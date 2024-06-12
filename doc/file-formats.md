# File Formats

<!-- markdownlint-disable MD001 -->
<!-- markdownlint-disable MD025 -->
<!-- markdownlint-disable MD030 -->

In this chapter, the formats of files AS generates shall be explained whose formats are not self-explanatory.

## Code Files

The format for code files generated by the assembler must be able to separate code parts that were generated for different target processors; therefore, it is a bit different from most other formats. Though the assembler package contains tools to deal with code files, I think is a question of good style to describe the format in short:

If a code file contains multi-byte values, they are stored in little endian order. This rule is already valid for the 16-bit magic word `$1489`, i.e. every code file starts with the byte sequence `$89`/`$14`.

This magic word is followed by an arbitrary number of "records". A record may either contain a continuous piece of the code or certain additional information. Even without switching to different processor types, a file may contain several code-containing records, in case that code or constant data areas are interrupted by reserved memory areas that should not be initialized. This way, the assembler tries to keep the file as short as possible.

Common to all records is a header byte which defines the record's type and its contents. Written in a PASCALish way, the record structure can be described in the following way:

```asm
FileRecord = RECORD CASE Header:Byte OF
        $00:(Creator:ARRAY[] OF Char);
        $01..
        $7f:(StartAdr : LongInt;
                Length   : Word;
                Data     : ARRAY[0...Length-1] OF Byte);
        $80:(EntryPoint:LongInt);
        $81:(Header   : Byte;
                Segment  : Byte;
                Gran     : Byte;
                StartAdr : LongInt;
                Length   : Word;
                Data     : ARRAY[0...Length-1] OF Byte);
        END
```

This description does not express fully that the length of data fields is variable and depends on the value of the `Length` entries.

A record with a header byte of $81 is a record that may contain code or data from arbitrary segments. The first byte (`Header`) describes the processor family the following code resp. data was generated for, as shown in the following table.

##### **Table:** Header Bytes for the Different Processor Families

<!-- markdownlint-disable MD056 -->

| Header | Family                   | Header | Family             |
| :----: | :----------------------- | :----: | :----------------- |
| `$01`  | 680x0, 6833x             | `$02`  | ATARI_VECTOR       |
| `$03`  | M\*Core                  | `$04`  | XGATE              |
| `$05`  | PowerPC                  | `$06`  | XCore              |
| `$07`  | TMS1000                  | `$08`  | NS32xxx            |
| `$09`  | DSP56xxx                 | `$0a`  | CP1600             |
| `$11`  | 65xx/MELPS-740           | `$12`  | MELPS-4500         |
| `$13`  | M16                      | `$14`  | M16C               |
| `$15`  | F<sup>2</sup>MC8L        | `$16`  | F<sup>2</sup>MC16L |
| `$19`  | 65816/MELPS-7700         | `$1a`  | PDK13              |
| `$1b`  | PDK14                    | `$1c`  | PDK15              |
| `$1d`  | PDK16                    | `$21`  | MCS-48             |
| `$25`  | SYM53C8xx                | `$27`  | KENBAK             |
| `$29`  | 29xxx                    | `$2a`  | i960               |
| `$31`  | MCS-51                   | `$32`  | ST9                |
| `$33`  | ST7                      | `$35`  | Z8000              |
| `$35`  | Super8                   | `$36`  | MN161x             |
| `$37`  | 2650                     | `$38`  | 1802/1805          |
| `$39`  | MCS-96/196/296           | `$3a`  | 8X30x              |
| `$3b`  | AVR                      | `$3c`  | XA                 |
| `$3d`  | AVR (8-Bit Code-Segment) | `$3e`  | 8008               |
| `$3f`  | 4004/4040                | `$40`  | H16                |
| `$41`  | 8080/8085                | `$42`  | 8086...V35         |
| `$43`  | SX20                     | `$44`  | F8                 |
| `$45`  | S12Z                     | `$46`  | 78K4               |
| `$47`  | TMS320C6x                | `$48`  | TMS9900            |
| `$49`  | TMS370xxx                | `$4a`  | MSP430             |
| `$4b`  | TMS320C54x               | `$4c`  | 80C166/167         |
| `$4d`  | OLMS-50                  | `$4e`  | OLMS-40            |
| `$4f`  | MIL STD 1750             | `$50`  | HMCS-400           |
| `$51`  | Z80/180/380              | `$52`  | TLCS-900           |
| `$53`  | TLCS-90                  | `$54`  | TLCS-870           |
| `$55`  | TLCS-47                  | `$56`  | TLCS-9000          |
| `$57`  | TLCS-870/C               | `$58`  | NEC 78K3           |
| `$59`  | eZ8                      | `$5a`  | TC9331             |
| `$5b`  | KCPSM3                   | `$5c`  | LatticeMico8       |
| `$5d`  | NEC 75xx                 | `$5e`  | 68RS08             |
| `$5f`  | COP4                     | `$60`  | 78K2               |
| `$61`  | 6800, 6301, 6811         | `$62`  | 6805/HC08          |
| `$63`  | 6809                     | `$64`  | 6804               |
| `$65`  | 68HC16                   | `$66`  | 68HC12             |
| `$67`  | ACE                      | `$68`  | H8/300(H)          |
| `$69`  | H8/500                   | `$6a`  | 807x               |
| `$6b`  | KCPSM                    | `$6c`  | SH7000             |
| `$6d`  | SC14xxx                  | `$6e`  | SC/MP              |
| `$6f`  | COP8                     | `$70`  | PIC16C8x           |
| `$71`  | PIC16C5x                 | `$72`  | PIC17C4x           |
| `$73`  | TMS-7000                 | `$74`  | TMS3201x           |
| `$75`  | TMS320C2x                | `$76`  | TMS320C3x/C4x      |
| `$77`  | TMS320C20x/C5x           | `$78`  | ST6                |
| `$79`  | Z8                       | `$7a`  | µPD78(C)10         |
| `$7b`  | 75K0                     | `$7c`  | 78K0               |
| `$7d`  | µPD7720                  | `$7e`  | µPD7725            |
| `$7f`  | µPD77230                 |

<!-- markdownlint-enable MD056 -->

The `Segment` field signifies the address space the following code belongs to. The assignment is defined in the following table.

##### **Table:** Codings of the `Segment` Field

| number | segment       | number | segment   |
| :----: | :------------ | :----: | :-------- |
| `$00`  | `<undefined>` | `$01`  | `CODE`    |
| `$02`  | `DATA`        | `$03`  | `IDATA`   |
| `$04`  | `XDATA`       | `$05`  | `YDATA`   |
| `$06`  | `BDATA`       | `$07`  | `IO`      |
| `$08`  | `REG`         | `$09`  | `ROMDATA` |

The `Gran` field describes the code's "granularity", i.e. the size of the smallest addressable unit in the following set of data. This value is a function of processor type and segment and is an important parameter for the interpretation of the following two fields that describe the block's start address and its length: While the start address refers to the granularity, the `Length` value is always expressed in bytes! For example, if the start address is $300 and the length is 12, the resulting end address would be $30b for a granularity of 1, however $303 for a granularity of 4! Granularities that differ from 1 are rare and mostly appear in DSP CPU's that are not designed for byte processing. For example, a DSP56K's address space is organized in 64 Kwords of 16 bits. The resulting storage capacity is 128 Kbytes, however it is organized as 2<sup>16</sup> words that are addressed with addresses 0, 1, 2, ...65535!

The start address is always 32 bits in size, independent of the processor family. In contrast, the length specification has only 16 bits, i.e. a record may have a maximum length of 4+4+2+(64K-1) = 65545 bytes.

Data records with a Header ranging from $01 to $7f present a shortcut and preserve backward compatibility to earlier definitions of the file format: in their case, the Header directly defines the processor type, the target segment is fixed to `CODE` and the granularity is implicitly given by the processor type, rounded up to the next power of two. AS prefers to use these records whenever data or code should go into the `CODE` segment.

A record with a Header of $80 defines an entry point, i.e. the address where execution of the program should start. Such a record is the result of an `END` statement with a corresponding address as argument.

The last record in a file bears the Header $00 and has only a string as data field. This string does not have an explicit length specification; its end is equal to the file's end. The string contains only the name of the program that created the file and has no further meaning.

## Debug Files

Debug files may optionally be generated by AS. They deliver important information for tools used after assembly, like disassemblers or debuggers. AS can generate debug files in one of three formats: On the one hand, the object format used by the AVR tools from Atmel respectively a NoICE-compatible command file, and on the other hand an own format. The first two are described in detail in [^AVRObj] resp. the NoICE documentations, which is why the following description limits itself to the AS-specific MAP format:

The information in a MAP file is split into three groups:

- symbol table
- memory usage per section
- machine addresses of source lines

The second item is listed first in the file. A single entry in this list consists of two numbers that are separated by a `:` character:

```asm
<line number>:<address>
```

Such an entry states that the machine code generated for the source statement in a certain line is stored at the mentioned address (written in hexadecimal notation). With such an information, a debugger can display the corresponding source lines while stepping through a program. As a program may consist of several include files, and due to the fact that a lot of processors have more than one address space (though admittedly only one of them is used to store executable code), the entries described above have to be sorted. AS does this sorting in two levels: The primary sorting criteria is the target segment, and the entries in one of these sections are sorted according to files. The sections resp. subsections are separated by special lines in the style of

```asm
Segment <segment name>
```

resp.

```asm
File <file name>
```

The source line info is followed by the symbol table. Similar to the source line info, the symbol table is primarily sorted by the segments individual symbols are assigned to. In contrast to the source line info, an additional section `NOTHING` exists which contains the symbols that are not assigned to any specific segment (e.g. symbols that have been defined with a simple `EQU` statement). A section in the symbol table is started with a line of the following type:

```asm
Symbols in Segment <segment name>
```

The symbols in a section are sorted according to the alphabetical order of their names, and one symbol entry consists of exactly one line. Such a line consists of six fields witch are separated by at least a single space:

The first field is the symbol's name, possibly extended by a section number enclosed in brackets. Such a section number limits the range of validity for a symbol. The second field designates the symbol's type: `Int` stands for integer values, `Float` for floating point numbers, and `String` for character arrays. The third field finally contains the symbol's value. If the symbol contains a string, it is necessary to use a special encoding for control characters and spaces. Without such a coding, spaces in a string could be misinterpreted as delimiters to the next field. AS uses the same syntax that is also valid for assembly source files: Instead of the character, its ASCII value with a leading backslash (`\`) is inserted. For example, the string

```asm
This is a test
```

becomes

```asm
This\032is\032\a\032test
```

The numerical value always has three digits and has to be interpreted as a decimal value. Naturally, the backslash itself also has to be coded this way.

The fourth field specifies - if available - the size of the data structure placed at the address given by the symbol. A debugger may use this information to automatically display variables in their correct length when they are referred symbolically. In case AS does not have any information about the symbol size, this field simply contains the value -1.

The fifth field states via the values 0 or 1 if the symbol has been used during assembly. A program that reads the symbol table can use this field to skip unused symbols as they are probably unused during the following debugging/disassembly session.

Finally, the sixth field states via the values 0 or 1 if the symbol is a constant (0) or variable(1). Constant symbols are set once, e.g. via the `EQU` statement or a label, while variables are allowed to change their value during the course of assembly. The MAP file lists the final value.

The third section in a debug file describes the program's sections in detail. The need for such a detailed description arises from the sections' ability to limit the validity range of symbols. A symbolic debugger for example cannot use certain symbols for a reverse translation, depending on the current PC value. It may also have to regard priorities for symbol usage when a value is represented by more than one symbol. The definition of a section starts with a line of the following form:

```asm
Info for Section nn ssss pp
```

`nn` specifies the section's number (the number that is also used in the symbol table as a postfix for symbol names), `ssss` gives its name and `pp` the number of its parent section. The last information is needed by a re-translator to step upward through a tree of sections until a fitting symbol is found. This first line is followed by a number of further lines that describe the code areas used by this section. Every single entry (exactly one entry per line) either describes a single address or an address range given by a lower and an upper bound (separation of lower and upper bound by a minus sign). These bounds are "inclusive", i.e. the bounds themselves also belong to the area. Is is important to note that an area belonging to a section is not additionally listed for the section's parent sections (an exception is of course a deliberate multiple allocation of address areas, but you would not do this, would you?). On the one hand, this allows an optimized storage of memory areas during assembly. On the other hand, this should not be an obstacle for symbol back-translation as the single entry already gives an unambiguous entry point for the symbol search path. The description of a section is ended by an empty line or the end of the debug file.

Program parts that lie out of any section are not listed separately. This implicit "root section" carries the number -1 and is also used as parent section for sections that do not have a real parent section.

It is possible that the file contains empty lines or comments (semi colon at line start). A program reading the file has to ignore such lines.

<!-- markdownlint-enable MD030 -->
<!-- markdownlint-enable MD025 -->
<!-- markdownlint-disable MD001 -->
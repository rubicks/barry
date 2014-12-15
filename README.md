barry [![Build Status](https://travis-ci.org/rubicks/barry.svg?branch=master)](https://travis-ci.org/rubicks/barry)
=======

```barry``` makes Byte ARRaYs.

You can use barry to make the contents of any file into a programmatic
resource. The resulting C language ```unsigned char[]``` can be opened with
```fmemopen``` to give a ```FILE*```.

No more messing with resource files and their paths---store the content directly
in your program.


### Examples

Read stdin implicitly

    $ echo "Hello, Barry!" | barry
    { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x42,
      0x61, 0x72, 0x72, 0x79, 0x21, 0x0a };

Read stdin explicitly

    $ echo "Hello, Barry!" | barry -
    { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x42,
      0x61, 0x72, 0x72, 0x79, 0x21, 0x0a };

Read stdin, declare named symbol

    $ echo "give me a name" | ./barry -n thingo
    unsigned char thingo [] =
    { 0x67, 0x69, 0x76, 0x65, 0x20, 0x6d, 0x65, 0x20,
      0x61, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x0a };

Read a file

    $ cat foo.txt
    This is foo content.

    $ barry foo.txt
    unsigned char foo_txt [] =
    { 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20,
      0x66, 0x6f, 0x6f, 0x20, 0x63, 0x6f, 0x6e, 0x74,
      0x65, 0x6e, 0x74, 0x2e, 0x0a };

Read a bunch of files

    $ cat bar.txt
    What's a bar?

    $ cat qux.txt
    I've got the qux.

    $ barry foo.txt bar.txt qux.txt
    unsigned char foo_txt [] =
    { 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20,
      0x66, 0x6f, 0x6f, 0x20, 0x63, 0x6f, 0x6e, 0x74,
      0x65, 0x6e, 0x74, 0x2e, 0x0a };
    unsigned char bar_txt [] =
    { 0x57, 0x68, 0x61, 0x74, 0x27, 0x73, 0x20, 0x61,
      0x20, 0x62, 0x61, 0x72, 0x3f, 0x0a };
    unsigned char qux_txt [] =
    { 0x49, 0x27, 0x76, 0x65, 0x20, 0x67, 0x6f, 0x74,
      0x20, 0x74, 0x68, 0x65, 0x20, 0x71, 0x75, 0x78,
      0x2e, 0x0a };

Write a file

    $ barry -o foobar.c foo.txt bar.txt

    $ cat foobar.c
    unsigned char foo_txt [] =
    { 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20,
      0x66, 0x6f, 0x6f, 0x20, 0x63, 0x6f, 0x6e, 0x74,
      0x65, 0x6e, 0x74, 0x2e, 0x0a };
    unsigned char bar_txt [] =
    { 0x57, 0x68, 0x61, 0x74, 0x27, 0x73, 0x20, 0x61,
      0x20, 0x62, 0x61, 0x72, 0x3f, 0x0a };


barry [![Build Status](https://travis-ci.org/rubicks/barry.svg?branch=master)](https://travis-ci.org/rubicks/barry)
=======

```barry``` makes Byte ARRays.

You can use barry to make the contents of any file into a programmatic
resource. The resulting C language ```unsigned char[]``` can be opened with
```fmemopen``` to give a ```FILE*```.

No more messing with resource files and their paths---store the content directly
in your program.

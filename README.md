# Printf-like function

Made for use with my [Interpreter](https://www.github.com/RicardoLuis0/Interpreter)

## Usage

* parameter format: `%[length][.precision][type]{position}`

    * %% is escape for percent

    * length: number, length to print, ignored if non-string

    * precision: number, precision, ignored if non-floating point

    * types:

        * `c`: print as character, ignored if non-integral

        * `f`: print as floating point, ignored if non-floating point

        * `x`: print as hex, ignored if non-numeric

        * `X`: print as uppercase hex, ignored if non-numeric

        * `e`: print as lowercase scientific notation, ignored if non-numeric

        * `E`: print as uppercase scientific notation, ignored if non-numeric

    * position: index of parameter in argument list, will not increment parameter index for non-positioned params

* examples:

    * `printf("%3{}",99)` : ` 99`

    * `printf("%03{}",99)` : `099`

    * `printf("%2{}",9999)` : `9999`

    * `printf("%{2} %{} %{}",11,12)` : `12 11 12`

    * `printf("%{}",'A')` : `65`

    * `printf("%c{}",'A')` : `A`

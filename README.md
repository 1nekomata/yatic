# yatic
Yet Another Thing I Created is a very basic(for now) Discord Bot that was Written in C using the [Orca Library](https://github.com/cee-studio/orca)

## Usage
Before building the Bot run `make update`.
Then build the Bot with `make build` and add your token within `config.json` or provide your own config file that you can use as an argument: `./yatic example_config.json`
To see all commands, type `yatic help me` in a Server that yatic has been added to.

## Notes
If the Error "Expected:       Could not create logger file" occurs create a directory called log or change where the logs are stored in config.json or your custom config

## Credit
[cee.studio](https://github.com/cee-studio) for the [Orca Library](https://github.com/cee-studio/orca)

Original idea by [patemathic](https://github.com/patemathic)

## Copyright notice of the Orca Library
```MIT License

Copyright (c) 2021 cee.studio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

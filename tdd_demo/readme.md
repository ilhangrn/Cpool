# Ceedling and Test
> Ceedling is a tool to create project based on tests. True approach of TDD. To install Ceedlings we need to install `ruby`. Because Ceedling will be installed by:

```sh
gem install ceedling
```

> After this we can create our project with

```sh
ceedling new my_demo
cd my_demo
```

> With this it craates a folder for our project:
    - src directory for project
    - test directory for its test
    - project.yml file for settings and configrations

> Now we have an empty project. We are going to add our first module:

```sh
ceedling module:create[printer]
```

> This gives us almost a complete setup ready for test with:

    - src/printer.c our empty source with header include
    - src/printer.h our header with guards
    - test/test_printer.c test functions for printer module
    - build/ directory with logs, test folders, cmock and unity frameworks. With their meson files for building.

> Was life this easy before. Why did we struggle that much. Just in one minute, i have written a sum function and tested it for three cases. All we do:
1. Declaration of it in header
```c
int sum(int a, int b);
```

2. Definition in source
```c
int sum(int a, int b)
{
    return 2 * ( a + b);
}
```

3.Adding tests to test_printer.c file like this `TEST_ASSERT_EQUAL_INT(6, sum(1,2))`

> Then we call
```sh
ceedling test:all
```

> This gives us test result. We tested a c code in seconds. Without gcc blabla things :)

> Here report: We have 3 tests but it says passed 1, and failed in 1. Because it does not continue when hits fail. We didn't have to write main function.

```yml
:source:
  :file: test/test_printer.c
  :dirname: test
  :basename: test_printer.c
:successes: []
:failures:
- :test: test_printer_sum_operation
  :line: 20
  :message: Expected 6 Was 8
  :unity_test_time: 0
:ignores: []
:counts:
  :total: 1
  :passed: 0
  :failed: 1
  :ignored: 0
:stdout: []
:time: 0.1426029999856837
```
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

> 
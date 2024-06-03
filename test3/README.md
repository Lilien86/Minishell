<img width="1728" alt="image" src="https://user-images.githubusercontent.com/26127185/175815870-be78bbd5-d1be-4164-954a-982768c6b147.png">

# Installation 
Clone the repo **inside** your minishell folder 
```sh
cd minishell
git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester/src
```

# How to run 
Run the `tester` file to run all the tests for the mandatory part of the project
```sh
./tester
./tester mandatory
./tester bonus
./tester not_required
./tester all
```
<p align="center">
  <img src="https://user-images.githubusercontent.com/26127185/175816613-324711eb-5511-4dea-84b6-3117d6b79d28.gif" width="720"/>
</p>

# Separate tests
You can also call `./tester` + `test_file` to run only a specific part of the test:
```sh
./tester builtins 
```
```sh
./tester pipes 
```
```sh
./tester redirects 
```
```sh
./tester extras 
```

# Manual tests 
The tester does **not** test everything. We added some suggestions of manual test in the [manual_tests](manual_tests) folder
- [mandatory](manual_tests/mandatory)
- [heredoc](manual_tests/heredoc)
- [signals](manual_tests/signals)
- [not_mandatory](manual_tests/not_mandatory)

# Bonus 
We also have tests for the `wildcards` part of the bonus: 
```
./tester wildcards
./tester bonus
./tester all
```
* Make sure your executable is called `minishell` or change the path in the tester line 3 `MINISHELL_PATH`

# Extra tests
We decided to leave out some tests from the mandatory part, things like syntax errors and OS specific code.
<p align="center">
  <img width="800" alt="Screen Shot 2022-06-26 at 10 40 18 AM" src="https://user-images.githubusercontent.com/26127185/175816956-d7358f24-6498-4c53-932f-183c9f0bd1ba.png">
</p>

You can run them like any other separate test:
```sh
./tester syntax
```
```sh
./tester os_specific
```

You can add tests by addings lines in files existing or by creating a file and add it in the tester with test_files

# How to run Valgrind Tester
# To run the valgrind tester you has to use the -c flags exemple of implementations :
```c
if (ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
	start_parse(ft_strdup(av[2]), &env, &exit_code); -> start your parsing with argv[2] as if it was a readline input command
else
	parsing with readline
```
Run the `vtester` file to run all the tests for the mandatory part of the project and bonus as below
```sh
./vtester
./vtester mandatory
./vtester wildcards
./vtester bonus
./tvester all
./vtester syntax
```

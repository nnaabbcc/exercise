# Use vimdiff as git diff tool

## add this to ~/.gitconfig

```
[diff]
  external = git_diff_wrapper
[pager]
  diff =
```

## create a file named git_diff_wrapper, put it somewhere in your $PATH

```shell
#!/bin/sh
vimdiff "$2" "$5"
```


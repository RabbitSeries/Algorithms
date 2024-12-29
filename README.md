# Algorithms

 Learning datastructs and algorithms.

## Configurations

```shell
git config --local http.proxy "socks5://127.0.0.1:10808"

git config --local https.proxy "socks5://127.0.0.1:10808"

git config --global user.name "RabbitArch"

git config --global user.email "<xiali23.ch@gmail.com>"

# Remember, sometimes need to check the local user name and email.
git config --local user.email "<xiali23.ch@gmail.com>"

git config --local user.name "RabbitArch"

git config list

git config --local main

[core]
 repositoryformatversion = 0
 filemode = false
 bare = false
 logallrefupdates = true
 symlinks = false
 ignorecase = true
[submodule]
 active = .
[remote "origin"]
 url = https://github.com/RabbitSeries/Algorithms.git
 fetch = +refs/heads/*:refs/remotes/origin/*
[branch "main"]
 remote = origin
 merge = refs/heads/main
 vscode-merge-base = origin/main
[lfs]
 repositoryformatversion = 0
[http]
 proxy = socks5://127.0.0.1:10810
[https]
 proxy = socks5://127.0.0.1:10810
```

```bash
# Update vscode on linux platform
# Prequirements: yay, sudo
yay -S visual-studio-code-bin
```

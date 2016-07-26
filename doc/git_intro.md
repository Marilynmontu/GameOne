# Git 常见用法

[TOC]

## 介绍

### 1.Git是什么？

维基百科：
> Git是一个**分布式版本控制**软件。

有道词典：
> git n. 饭桶

### 2.什么是版本控制？

管理文件的更改。

### 3.怎么实现？

记录历史。

拿出你家的相册，抽出你5岁时的照片、7岁时的照片、12岁时的照片…拿相邻的两张去对比，14岁版本的你和15岁版本的你不同，你长高了，或者青春痘的数量变了？你已经在做版本控制了。

### 4.可是这有什么用？

合作。

对于小型项目而言，不仅没用，可能还是累赘。如果有人每天花太多时间观察自己代码的历史，那他肯定有一点自恋的倾向。

但如果项目的规模变大，或人手增多，版本控制的价值就会凸显。一个文件里的源代码，随着项目开展会越来越多，它们是一点点变多的——上个月，Bob增加了背景引擎，上星期，Alice让玩家能够跳跃，未来一星期，小组打算修复一个计分的bug，这个任务分配给了David。这些活动都给player.cpp造成了更改。版本控制系统会把谁在何时做了什么更改记录下来，如果有段代码特难懂，或者造成了程序崩溃，可以很容易找到责任人。

版本控制系统能帮你合并更改，比如Bob修改了某文件中的func1()，而Alice在同一时间修改了其中的func2()，他们提交后，这个文件会包含二人的更改。版本控制系统把他们的工作成果合并了。

还有一个用途：备份。文件被改得面目全非？或者意外删除？把上一个版本_签出_即可。

### 5.我该从哪里开始？

选一款软件。

下面是Git的教程。企业一般用SVN（SVN与Git类似，也很不错），不过学习Git能让你快速入手GitHub，你能接触到很多开源软件，而且马上就拥有完全自己控制的代码库，于是你得到了全貌。在企业你很难如此。

学习[**基础知识**](http://www.ruanyifeng.com/blog/2008/12/a_visual_guide_to_version_control.html)。

## 预备知识

(DOS和Shell命令)

(vim和less快捷键)

## 配置

```
git config --global user.name '你的名字'
git config --global user.email '你的E-mail'
git config --global alias.co checkout
```

## 工作流

### 1.初始化版本库

```
git init
```

这条命令执行之后，当前文件夹就变成了一个Git版本库。

### 2.创建新文件/修改已有文件

### 3.查看更改状态

列出发生变更的文件：

```
git status
```

用less查看对已有文件的改动：

```
git diff
```

### 4.提交到版本库

（关于message）

提交所有改动：
```
git add -A
git commit -m "MESSAGE"
```

只提交file1和file2的改动：

```
git add file1 file2
git commit -m "MESSAGE"
```

只提交对已有文件的更改，忽略新文件：

```
git commit -am "MESSAGE"
```

写下多段说明：

```
git add ...
git commit -m "MESSAGE_0" -m "MESSAGE_1" -m "MESSAGE_2"
```

查看已有的提交：

```
git log
```

### 5.撤销文件更改

撤销对file的改动：

```
git checkout -- file
```

撤销所有改动（**十分危险！！！**）：

```
git checkout
```

### 6.重复

重复2-5.

## 远程仓库

远程仓库是你仓库的备份，它在世界的另一个角落。远程仓库通常由GitHub这样的网站提供，GitHub上建立的仓库都是公开的，任何人都能看到，不想这样你就要掏美金。要是隐私对你很重要，可以试试BitBucket，它提供免费的私有仓库。但它在国内访问不稳定，我们国家防火墙太厚。

Git提供了一对命令来实现与远程仓库交互：push，用来把本地（相对与“远程”而言）的更改更新到远程；pull，用来把远程的变化同步到本地。

如果参与开发的只有你一人（通常如此，孤独的程序员啊），一般本地仓库会比远程仓库超前。这时进行push就会把自从上次以来，远程仓库落下的更改发送到远程仓库。

如果你使用GitHub的在线编辑器提交了改动，本地分支就会落后。你需要执行pull把新的改动接收到本地。还有更复杂的情况：在远程的改动_还没有_刷到本地时，本地出现了新的改动。这时你push会失败，它会被拒收。你必须先pull。pull在接收远程改动之后，会执行一次_合并_，之后再push就没问题了。

### 管理

列出所有远程仓库：

```
git remote -v
```

添加远程仓库，起名叫origin：

```
git remote add origin http://github.com/USER/REPO.git
```

**记住**：给默认的远程仓库起名叫origin就对了。

### 推送

把本地更改更新到远程仓库：

```
git push
```

如果这是你添加远程仓库后第一次push：

```
git push -u origin master
```

**说明**：这条语句告诉git，

### 取回

把远程仓库的变化同步到本地：

```
git pull
```

**注**：如果本地和远程各有各的更改（如上面所述），pull_合并_远程到本地会产生一次新的提交，这时会弹出vim编辑器要你输入这次提交的message。你可以输入<code>:wq</code>，保留默认message，结束。vim编辑器的使用参见上面的“预备知识”。

仅仅取回，不同步：

```
git fetch
```

与取回的远程分支master同步：

```
git merge origin/master
```

## 分支

### 分支操作

### 分支与远程仓库

## 复杂情况

(手工忽略文件)
(使用.gitignore)

## FAQ

### 上一次的Commit Message写错，怎么修改

### 撤销上次Commit

### The current branch master has no upstream branch.

```
fatal: The current branch master has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin master
```

```
git push -u origin master
```

```
git fetch
git branch -u origin/master
```


### git 指令学习

#### 基础篇

##### git commit

进行提交指令，每次进行提交时，它并不会盲目地复制整个目录。条件允许的情况下，它会将当前版本与仓库中的上一个版本进行对比，并把所有的差异打包到一起作为一个提交记录。

###### git commit --amend



##### git branch

后加分支名<name>，表示创建一个分支。

##### git checkout

后加分支名<name>，表示切换分支，接下来的提交修改会在该分支上进行。

后加哈希值<C>，表示切换到对应parent节点，接下来的提交修改会在该节点上进行。

###### git checkout -b

后加分支名<name>，表示创建一个分支，并切换至该创建的新分支

##### git merge

后加分支名<name>，表示将<name>分支和当前所在分支合并到一起，在 Git 中合并两个分支时会产生一个特殊的提交记录，它有两个 parent 节点。

##### git rebase

后加分支名<name1>，表示将当前所在分支<name2>移动到<name1>分支上，这时切换到<name1>上，通过`git rebase <name2>`可以实现两个分支的合并

#### 高级篇

##### HEAD

HEAD 是一个对当前所在分支的符号引用 —— 也就是指向你正在其基础上进行工作的提交记录。

HEAD 总是指向当前分支上最近一次提交记录。大多数修改提交树的 Git 命令都是从改变 HEAD 的指向开始的。

HEAD 通常情况下是指向分支名的。

如果想看 HEAD 指向，可以通过 `cat .git/HEAD` 查看， 如果 HEAD 指向的是一个引用，还可以用 `git symbolic-ref HEAD` 查看它的指向。

##### 相对引用

通过在引用名称后加上操作符，表示让 Git 寻找指定提交记录的 parent 提交。

- 使用 `^` 向上移动 1 个提交记录
- 使用 `~<num>` 向上移动多个提交记录，如 `~3`

##### 强制修改分支位置

###### git branch -f  <name>  <parent>

上面的命令会将 分支<name>强制指向 HEAD 的<parent>提交。

##### 撤销变更

`git reset <parent>` 通过把分支记录回退几个提交记录来实现撤销改动。在reset后，  所做的变更还在，但是处于未加入暂存区状态。

`git revert <parent>`  通过新提交记录引入了**更改** —— 这些更改刚好是用来撤销这个提交的。revert 之后就可以把你的更改推送到远程仓库与别人分享。

#### 移动提交记录

##### 整理提交记录

`git cherry-pick <name>`将<name>**复制**到当前所在的位置（`HEAD`）下面

##### 交互式的 rebase

`git rebase -i <parent>`使用该指令Git 会打开一个 UI 界面并列出将要被复制到目标分支的备选提交记录，它还会显示每个提交记录的哈希值和提交说明，提交说明有助于你理解这个提交进行了哪些更改。

当 rebase UI界面打开时, 你能做3件事:

- 调整提交记录的顺序（通过鼠标拖放来完成）
- 删除你不想要的提交（通过切换 `pick` 的状态来完成，关闭就意味着你不想要这个提交记录）
- 合并提交。允许你把多个提交记录合并成一个。

#### 杂项

##### git tag <tag> <name>

创建一个标签命名为 <tag>，并且明确地让它指向提交记录 <name>,不能直接在<tag>上面做 commit。

##### git describe <ref>

`<ref>` 可以是任何能被 Git 识别成提交记录的引用，如果你没有指定的话，Git 会使用你目前所在的位置（`HEAD`）。

它输出的结果是这样的：

```
<tag>_<numCommits>_g<hash>
```

`tag` 表示的是离 `ref` 最近的标签， `numCommits` 是表示这个 `ref` 与 `tag` 相差有多少个提交记录， `hash` 表示的是你所给定的 `ref` 所表示的提交记录哈希值的前几位。

当 `ref` 提交记录上有某个标签时，则只输出标签名称

#### 远程操作

##### git clone

 命令在真实的环境下的作用是在**本地**创建一个远程仓库的拷贝（比如从 github.com）。

##### git fetch

`git fetch` 完成了仅有的但是很重要的两步:

- 从远程仓库下载本地仓库中缺失的提交记录
- 更新远程分支指针(如 `o/main`)

`git fetch` 实际上将本地仓库中的远程分支更新成了远程仓库相应分支最新的状态。

如果你还记得上一节课程中我们说过的，远程分支反映了远程仓库在你**最后一次与它通信时**的状态，`git fetch` 就是你与远程仓库通信的方式了！希望我说的够明白了，你已经了解 `git fetch` 与远程分支之间的关系了吧。

`git fetch` 通常通过互联网（使用 `http://` 或 `git://` 协议) 与远程仓库通信。

`git fetch` 并不会改变你本地仓库的状态。它不会更新你的 `main` 分支，也不会修改你磁盘上的文件。

##### git pull

 `git pull` 就是 git fetch 和 git merge 的缩写，进行先抓取更新再合并到本地分支的操作。

##### git push

`git push` 负责将**你的**变更上传到指定的远程仓库，并在远程仓库上合并你的新提交记录

当你的工作就变成了基于项目**旧版**的代码，与远程仓库最新的代码不匹配了。Git 是不会允许你 `push` 变更的。实际上它会强制你先合并远程最新的代码，然后才能分享你的工作。

 `git pull --rebase` 就是 fetch 和 rebase 的简写，可以用它来解决上述问题。


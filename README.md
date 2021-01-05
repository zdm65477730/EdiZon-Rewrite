# EdiZon

  <p align="center"><img src="https://raw.githubusercontent.com/WerWolv/EdiZon-Rewrite/master/icon.jpg"><br />
      <a href="https://github.com/WerWolv/EdiZon-Rewrite/releases/latest"><img src="https://img.shields.io/github/downloads/WerWolv/EdiZon-Rewrite/total.svg" alt="Latest Release" /></a>
    <a href="https://discord.gg/qyA38T8"><img src="https://discordapp.com/api/guilds/465980502206054400/embed.png" alt="Discord Server" /></a>
    <a href="https://travis-ci.com/WerWolv/EdiZon-Rewrite"><img src="https://travis-ci.com/WerWolv/EdiZon-Rewrite.svg?branch=master" alt="Build Status" /></a>
  </p>

具有存档文件管理器、编辑器、金手指引擎、金手指创建和Horizon（任天堂Switch的操作系统）按钮序列映射功能的自制软件。

## 概述

EdiZon包含6个主要功能如下

  - **存档文件管理**
    - 提取游戏保存档。
    - 注入提取的游戏存档(您自己和您的朋友存档文件)。
    - 一次提取并导入在设备上找到的所有存档文件。
    - 导入存档文件时创建存档文件系统(无需先打开每个游戏！)
    - 自动备份所有存档的文件，并可以选择将它们上传到远程服务器
    - 将存档文件直接上传到https://anonfile.com。
    - 批量提取系统上所有游戏的所有存档文件
  - **存档文件库**
    - 开源服务器可在线托管存档存档存储库，以供所有人访问
    - Mario Maker 2的官方库，100％文件等
  - **存档文件编辑**
    - 在控制台存档编辑中易于使用，可编写脚本并易于扩展。
      - Lua和Python脚本支持。
    - 内置的存档编辑器更新程序。
  - **动态内存编辑**
    - 金手指引擎，例如RAM编辑。
    - 通过Atmosphère的金手指模块冻结RAM中的值。
    - 用于加载、管理和更新Atmosphère金手指文件的界面。
    - 屏幕overlay插件，可管理金手指并修改RAM，而无需离开正在玩的游戏
  - **虚拟控制器按钮映射**
    - 按键组合和按键顺序可映射到任何joycon按键
    - 将控制器输入从计算机重定向到Switch，反之亦然

  全部打包成一个易于使用和易于安装的自制软件。

## Images

  <p align="center"><img src="https://raw.githubusercontent.com/WerWolv/EdiZon/master/assets/main_menu.jpg"></p>
  <p align="center"><img src="https://raw.githubusercontent.com/WerWolv/EdiZon/master/assets/save_editor_1.jpg"></p>
  <p align="center"><img src="https://raw.githubusercontent.com/WerWolv/EdiZon/master/assets/save_editor_2.jpg"></p>
  <p align="center"><img src="https://raw.githubusercontent.com/WerWolv/EdiZon/master/assets/ram_editor.jpg"></p>

## 存档编辑器配置和脚本文件

  要下载有效的Editor Config和Editor Script文件，请访问 [库](https://github.com/WerWolv/EdiZon_ConfigsAndScripts/tree/master)

  查看我们的 [Wiki页面](https://github.com/WerWolv/EdiZon/wiki) 获取更多有关如何构建自己的Editor Config和Editor Script文件的信息。

## 如何安装

  1. 从以下位置下载最新发行版本 [GitHub发行页面](https://github.com/WerWolv/EdiZon/releases/latest).
  2. 解压缩下载的zip文件，将文件放在Nintendo Switch的SD卡上，然后覆盖文件夹。
  3. 使用免费的开源CFW，例如 [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere)，启动hbmenu并从此处启动EdiZon
     1. 如果您想使用金手指管理器，则必须使用 [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere) 因为仅支持他们的金手指服务。
     2. 为了获得最佳体验，请打开文件 `/atmosphere/system_settings.ini` 并修改  `dmnt_cheats_enabled_by_default = u8!0x1` 为 `dmnt_cheats_enabled_by_default = u8!0x0`.


## 如何编译

  1. 使用 `git clone https://github.com/WerWolv/EdiZon --recurse-submodules` 将EdiZon存储库克隆到您的计算机。
  2. 下载并安装devkitA64。它与 [devkitPro](https://devkitpro.org) 工具链打包在一起.
  3. 使用devkitPro附带的pacman软件包管理器下载并安装libnx、Switch protlibs (`switch-portlibs`)、Switch OpenGL库 (`switch-glfw`、`switch-mesa`与`switch-glm`).
  4. 使用make命令来执行剩余的编译工作。键入`make application`以仅构建EdiZon，键入`make sysmodule`以仅构建配套的系统子模块，或键入`make`以构建所有内容。
  5. 如果要使用内置在makefile中的调试实用程序，则还需要在计算机上安装`python3`和`lftp`以及安装[sys-ftpd][sys-ftpd](https://github.com/jakibaki/sys-ftpd)到您的Switch机器里。

## Discord

  要获得有关使用EdiZon或创建存档编辑器配置和脚本的支持，请随时加入Discord上的EdiZon服务器：https://discord.gg/qyA38T8

## 致敬

  感谢...

  - [devkitPro](https://devkitpro.org) 贡献令人惊叹的工具链！
  - [SwitchBrew](https://switchbrew.org/) [Homebrew Launcher](https://github.com/switchbrew/nx-hbmenu) 贡献GUI和共享字体代码
  - [jakibaki](https://github.com/jakibaki) 为实现RAM编辑和sys-netcheat提供了巨大的帮助并受其启发。
  - [averne](https://github.com/averne) 他们对overlay图和代码的实现进行了惊人的研究。
  - [SciresM](https://github.com/SciresM) 贡献支持aarch64硬件加速的SHA256代码、libstratosphere、Atmosphère金手指引擎的实现以及提供开发过程中的支持。
  - [onepiecefreak](https://github.com/onepiecefreak3) 在开发过程中通常会有所帮助
  - [Ac_K](https://github.com/AcK77) 提供服务器端更新脚本的帮助、EdiZon存档网站以及堆IPC调用的逆向工程。
  - **kardch** 当前软件使用的漂亮的图标。
  - **bernv3** 之前软件使用的漂亮的图标。
  - **All save editor and cheat creators** 使这个项目进入到了大家的生活！

  <br>

  - [nlohmann](https://github.com/nlohmann) 提供了很棒的json库。
  - [Lua](https://www.lua.org/) 提供了脚本语言。
  - [Python](https://www.python.org/) 和 [nx-python](https://github.com/nx-python) 提供了脚本语言。


  <br>
  <p align="center"><img src="https://www.lua.org/images/logo.gif">
  <img src="https://upload.wikimedia.org/wikipedia/commons/c/c3/Python-logo-notext.svg"><p>

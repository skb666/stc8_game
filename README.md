# stc8_game

**说明**: 因片上资源有限，没有上多功能多效果的gui，ui设计的有点丑，大家按照喜好随便改哈 ”（￣▽￣）。。。然后flash也快耗尽，争取加上第三个游戏。

对这个项目有兴趣的也可以购入stc16系列继续开发，天问51系列的stc8与stc16板子引脚兼容，可以直接替换。

**板型**: 天问51（STC8H8K64U）

**开发平台**: win10   keil5

**控制方式**: IR红外遥控器控制、板上矩阵键盘

- 2048

    | IR按键  | 矩阵键盘              | 功能                                                  |
    | ------- | --------------------- | ----------------------------------------------------- |
    | 方向键  | '+'、'÷'、'-'、'x' 键 | 上下左右                                              |
    | '#' 键  | '#' 键                | 重新开始                                              |
    | '*' 键  | '*' 键                | 切换到贪吃蛇                                          |
    | 'ok' 键 | '0' 键                | 继续游戏(win时)/开始游戏(初始界面时)/重新开始(lose时) |

- 贪吃蛇

    | IR按键           | 矩阵键盘              | 功能                                    |
    | ---------------- | --------------------- | --------------------------------------- |
    | 方向键           | '+'、'÷'、'-'、'x' 键 | 上下左右                                |
    | '#' 键           | '#' 键                | 重新开始                                |
    | '*' 键           | '*' 键                | 切换到2048                              |
    | 'ok' 键          | '0' 键                | 暂停游戏/继续游戏/重新开始(win/lose 时) |
    | '4'、'5'、'6' 键 | '4'、'5'、'6' 键      | 低速、中速、快速                        |

**开发进度**:

- [x] 游戏主体实现
    - [x] 2048
      - [x] 游戏界面绘制
      - [x] 游戏逻辑实现
      - [x] 计分系统 
    - [x] 贪吃蛇
      - [x] 游戏界面绘制
      - [x] 游戏逻辑实现
      - [x] 计分、调速
    - [ ] ~~扫雷~~ 
    - [ ] ~~数独~~
    - [ ] ~~五子棋~~ 
- [x] 游戏选择
- [x] 优化

**坑**:

- eeprom多次写入，在写入前需要先擦除扇区，否则数据无法写入
- 将要读取、动态存储到eeprom的变量统一进行管理，可解决读写冲突
- 在使用malloc等动态内存管理函数前必须先用init_mempool初始化内存池
- 贪吃蛇按键处理上分线程会导致离奇game over的bug，改用协程

**附图**:

![2048_init](./img/1.jpg)

![2048_lose](./img/2.jpg)

![2048_win](./img/3.jpg)

![snake_run](./img/5.jpg)

![snake_lose](./img/4.jpg)
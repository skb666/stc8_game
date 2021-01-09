#include "game_2048.h"

// 2048游戏数据
uint16 data2048[4][4];
uint16 Target = 2048;
int score=0, best=0;
enum{
    S_FAIL = 0,
    S_WIN,
    S_NORMAL,
    S_QUIT
}gameStatus;

// "2048" 字模(32x32)
code const uint8 str_2048[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x38,0x78,
    0x00,0x00,0x70,0x38,0x00,0x00,0xF0,0x38,0x00,0x00,0xF0,0x78,0x00,0x00,0xF0,0x78,
    0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0xE0,0x00,0x00,0x01,0xC0,0x00,0x00,0x03,0x80,
    0x00,0x00,0x07,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x70,0x00,
    0x00,0x00,0xE0,0x00,0x00,0x01,0x80,0x00,0x00,0x03,0x01,0x80,0x00,0x0E,0x03,0x00,
    0x00,0x1C,0x06,0x00,0x00,0x3F,0xFE,0x00,0x00,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*２*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x00,0x00,0x1C,0x70,
    0x00,0x00,0x38,0x70,0x00,0x00,0x70,0x70,0x00,0x00,0x60,0x70,0x00,0x00,0xE0,0x70,
    0x00,0x00,0xE0,0x70,0x00,0x01,0xC0,0xE0,0x00,0x01,0xC0,0xE0,0x00,0x03,0x80,0xE0,
    0x00,0x03,0x81,0xC0,0x00,0x03,0x81,0xC0,0x00,0x07,0x03,0xC0,0x00,0x07,0x03,0x80,
    0x00,0x07,0x03,0x80,0x00,0x07,0x07,0x00,0x00,0x0F,0x07,0x00,0x00,0x0E,0x0E,0x00,
    0x00,0x06,0x1C,0x00,0x00,0x07,0x38,0x00,0x00,0x03,0xF0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*０*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0xE0,
    0x00,0x00,0x01,0xE0,0x00,0x00,0x03,0xE0,0x00,0x00,0x07,0xC0,0x00,0x00,0x0F,0xC0,
    0x00,0x00,0x1B,0xC0,0x00,0x00,0x33,0x80,0x00,0x00,0x67,0x80,0x00,0x00,0xC7,0x00,
    0x00,0x01,0x87,0x00,0x00,0x03,0x0F,0x00,0x00,0x06,0x0E,0x00,0x00,0x0C,0x0E,0x00,
    0x00,0x1F,0xFF,0xC0,0x00,0x3F,0xFF,0xC0,0x00,0x00,0x1C,0x00,0x00,0x00,0x3C,0x00,
    0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*４*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x1C,0x38,
    0x00,0x00,0x38,0x38,0x00,0x00,0x70,0x38,0x00,0x00,0xF0,0x38,0x00,0x00,0xF0,0x70,
    0x00,0x00,0xF0,0x60,0x00,0x00,0xF1,0xC0,0x00,0x00,0x7F,0x80,0x00,0x00,0x3E,0x00,
    0x00,0x00,0x7F,0x00,0x00,0x01,0xCF,0x80,0x00,0x03,0x87,0xC0,0x00,0x07,0x03,0xC0,
    0x00,0x0E,0x03,0xC0,0x00,0x0C,0x03,0xC0,0x00,0x0C,0x03,0x80,0x00,0x0C,0x07,0x00,
    0x00,0x0E,0x0E,0x00,0x00,0x07,0xBC,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*８*/
};

// 随机生成一个2或4
uint8 generate_randNum(){
    uint8 i, j, value;
    uint8 t[16], cnt=0;
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(data2048[i][j] == 0)
                t[cnt++] = i*4+j;
    if(!cnt) return 0;
    value = t[rand()%cnt];
    data2048[value/4][value%4] = (rand()%10==1) ? 4 : 2;
    return 1;
}

// 向左移动
uint8 moveLeft(){
    int8 i, j, currentWritePos;
    uint16 lastValue, tmp[4][4];
    for(i=0; i<4; ++i){
        currentWritePos = 0;
        lastValue = 0;
        for(j=0; j<4; ++j){
            tmp[i][j] = data2048[i][j];
            if(!data2048[i][j]) continue;
            if(lastValue == 0){
                lastValue = data2048[i][j];
            }else{
                if(lastValue == data2048[i][j]){
                    data2048[i][currentWritePos] = lastValue*2;
                    score += lastValue*2;
                    lastValue = 0;
                    if(data2048[i][currentWritePos] == Target) gameStatus = S_WIN;
                }else{
                    data2048[i][currentWritePos] = lastValue;
                    lastValue = data2048[i][j];
                }
                ++currentWritePos;
            }
            data2048[i][j] = 0;
            if(lastValue) data2048[i][currentWritePos] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(data2048[i][j] != tmp[i][j]) return 1;
    return 0;
}

// 向右移动
uint8 moveRight(){
    int8 i, j, currentWritePos;
    uint16 lastValue, tmp[4][4];
    for(i=0; i<4; ++i){
        currentWritePos = 3;
        lastValue = 0;
        for(j=3; j>=0; --j){
            tmp[i][j] = data2048[i][j];
            if(!data2048[i][j]) continue;
            if(lastValue == 0){
                lastValue = data2048[i][j];
            }else{
                if(lastValue == data2048[i][j]){
                    data2048[i][currentWritePos] = lastValue*2;
                    score += lastValue*2;
                    lastValue = 0;
                    if(data2048[i][currentWritePos] == Target) gameStatus = S_WIN;
                }else{
                    data2048[i][currentWritePos] = lastValue;
                    lastValue = data2048[i][j];
                }
                --currentWritePos;
            }
            data2048[i][j] = 0;
            if(lastValue) data2048[i][currentWritePos] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(data2048[i][j] != tmp[i][j]) return 1;
    return 0;
}

// 向上移动
uint8 moveUp(){
    int8 i, j, currentWritePos;
    uint16 lastValue, tmp[4][4];
    for(j=0; j<4; ++j){
        currentWritePos = 0;
        lastValue = 0;
        for(i=0; i<4; ++i){
            tmp[i][j] = data2048[i][j];
            if(!data2048[i][j]) continue;
            if(lastValue == 0){
                lastValue = data2048[i][j];
            }else{
                if(lastValue == data2048[i][j]){
                    data2048[currentWritePos][j] = lastValue*2;
                    score += lastValue*2;
                    lastValue = 0;
                    if(data2048[currentWritePos][j] == Target) gameStatus = S_WIN;
                }else{
                    data2048[currentWritePos][j] = lastValue;
                    lastValue = data2048[i][j];
                }
                ++currentWritePos;
            }
            data2048[i][j] = 0;
            if(lastValue) data2048[currentWritePos][j] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(data2048[i][j] != tmp[i][j]) return 1;
    return 0;
}

// 向下移动
uint8 moveDown(){
    int8 i, j, currentWritePos;
    uint16 lastValue, tmp[4][4];
    for(j=0; j<4; ++j){
        currentWritePos = 3;
        lastValue = 0;
        for(i=3; i>=0; --i){
            tmp[i][j] = data2048[i][j];
            if(!data2048[i][j]) continue;
            if(lastValue == 0){
                lastValue = data2048[i][j];
            }else{
                if(lastValue == data2048[i][j]){
                    data2048[currentWritePos][j] = lastValue*2;
                    score += lastValue*2;
                    lastValue = 0;
                    if(data2048[currentWritePos][j] == Target) gameStatus = S_WIN;
                }else{
                    data2048[currentWritePos][j] = lastValue;
                    lastValue = data2048[i][j];
                }
                --currentWritePos;
            }
            data2048[i][j] = 0;
            if(lastValue) data2048[currentWritePos][j] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(data2048[i][j] != tmp[i][j]) return 1;
    return 0;
}

// 重新开始游戏
void restart(){
    uint8 i, j;
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            data2048[i][j] = 0;
    generate_randNum();
    generate_randNum();
    score = 0;
    gameStatus = S_NORMAL;
}

// 判断游戏结束
uint8 isOver(){
    uint8 i, j;
    for(i=0; i<4; ++i){
        for(j=0; j<4; ++j){
            if(!data2048[i][j]) return 0;
            if ((j+1 < 4) && (data2048[i][j] == data2048[i][j+1]))
                return 0;
            if ((i+1 < 4) && (data2048[i][j] == data2048[i+1][j]))
                return 0;
        }
    }
    return 1;
}

// 设置测试数据
void setTestData(){
    uint8 i, j;
    int t = 50;
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            data2048[i][j] = 16 << i << j;
    score = 0;
    best = eeprom_read_int(0);
    if(best<0){
        best = 0;
        eeprom_sector_erase(0);
        eeprom_write_int(0, best);
    }
}

// 2048初始化游戏界面
void game2048_init(){
    uint8 i, j;
    tft_lcd_clear(TFT_LCD_LGRAY);
    tft_lcd_show_font32(4,str_2048,56,8,TFT_LCD_BRRED,TFT_LCD_WHITE,1);
    tft_lcd_draw_rectangle(19, 91, 221, 293, TFT_LCD_BLACK);
    tft_lcd_fill_rectangle(20, 92, 220, 292, TFT_LCD_LGRAYBLUE);
    tft_lcd_show_string(20,50,"Best :",TFT_LCD_BLACK,TFT_LCD_LGRAY,16,1);
    tft_lcd_show_string(20,68,"Score:",TFT_LCD_BLACK,TFT_LCD_LGRAY,16,1);
    for(i=0; i<5; ++i){
        tft_lcd_draw_line(20, 92+50*i, 220, 92+50*i, TFT_LCD_GRAYBLUE);
        tft_lcd_draw_line(20+50*i, 92, 20+50*i, 292, TFT_LCD_GRAYBLUE);
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            tft_lcd_draw_rectangle(23+j*50, 95+i*50, 67+j*50, 139+i*50, TFT_LCD_LIGHTBLUE);

    gameStatus = S_NORMAL;
    setTestData();
}

// 处理输入
void game2048_updateStatus(uint8 key){
    uint8 updated = 0;

    switch(key){
        case 'q':
            gameStatus = S_QUIT;
            break;
        case 'r':
            restart();
            break;
        case 'a':
            if(gameStatus == S_NORMAL) updated = moveLeft();
            break;
        case 'd':
            if(gameStatus == S_NORMAL) updated = moveRight();
            break;
        case 'w':
            if(gameStatus == S_NORMAL) updated = moveUp();
            break;
        case 's':
            if(gameStatus == S_NORMAL) updated = moveDown();
            break;
    }
    
    if(updated){
        generate_randNum();
        if(isOver()) gameStatus = S_FAIL;
        if(score>best){
            best = score;
            eeprom_sector_erase(0);
            eeprom_write_int(0, best);
        }
    }
}

// 运行游戏
void game2048_run(){
    uint8 buf[50], slen;
    uint8 i, j;
    
    if(gameStatus != S_QUIT){
        // 显示历史最高分、当前得分
        sprintf(buf, "%19d", best);
        tft_lcd_show_string(68,50,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
        sprintf(buf, "%19d", score);
        tft_lcd_show_string(68,68,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
        
        // 显示各格内数据
        for(i=0; i<4; ++i){
            for(j=0; j<4; ++j){
                if(data2048[i][j]){
                    switch(data2048[i][j]){
                        case 2:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_LIGHTGREEN);
                            break;
                        case 4:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_BRRED);
                            break;
                        case 8:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_GREEN);
                            break;
                        case 16:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_DARKBLUE);
                            break;
                        case 32:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_BLUE);
                            break;
                        case 64:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_RED);
                            break;
                        case 128:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_BRED);
                            break;
                        case 256:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_BROWN);
                            break;
                        case 512:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_LBBLUE);
                            break;
                        case 1024:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_GRAY);
                            break;
                        case 2048:
                            tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_BLACK);
                            break;
                    }
                    sprintf(buf, "%d", (int)data2048[i][j]);
                    slen = strlen(buf);
                    tft_lcd_show_string(45+50*j-4*slen,109+50*i,buf,TFT_LCD_WHITE,TFT_LCD_LGRAYBLUE,16,1);
                }else{
                    tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_LGRAYBLUE);
                }
            }
        }

        if(gameStatus == S_WIN)
            tft_lcd_show_string(36,300,"          You Win !         ",TFT_LCD_RED,TFT_LCD_LGRAY,12,0);
        else if(gameStatus == S_FAIL)
            tft_lcd_show_string(36,300,"          You Lose!         ",TFT_LCD_RED,TFT_LCD_LGRAY,12,0);
        else
            tft_lcd_show_string(36,300,"Join the tiles, get to 2048!",TFT_LCD_BROWN,TFT_LCD_LGRAY,12,0);
    }
}

#include "game.h"

// 2048游戏数据
uint16 Target = 2048;
gameData_2048 gd_2048;

// 随机生成一个2或4
uint8 generate_randNum(){
    uint8 i, j, value;
    uint8 t[16], cnt=0;
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(gd_2048.Data[i][j] == 0)
                t[cnt++] = i*4+j;
    if(!cnt) return 0;
    value = t[rand()%cnt];
    gd_2048.Data[value/4][value%4] = (rand()%10==1) ? 4 : 2;
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
            tmp[i][j] = gd_2048.Data[i][j];
            if(!gd_2048.Data[i][j]) continue;
            if(lastValue == 0){
                lastValue = gd_2048.Data[i][j];
            }else{
                if(lastValue == gd_2048.Data[i][j]){
                    gd_2048.Data[i][currentWritePos] = lastValue*2;
                    gd_2048.Score += lastValue*2;
                    lastValue = 0;
                    if(gd_2048.Data[i][currentWritePos] == Target)
                        gd_2048.Status = S_WIN;
                }else{
                    gd_2048.Data[i][currentWritePos] = lastValue;
                    lastValue = gd_2048.Data[i][j];
                }
                ++currentWritePos;
            }
            gd_2048.Data[i][j] = 0;
            if(lastValue) gd_2048.Data[i][currentWritePos] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(gd_2048.Data[i][j] != tmp[i][j]) return 1;
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
            tmp[i][j] = gd_2048.Data[i][j];
            if(!gd_2048.Data[i][j]) continue;
            if(lastValue == 0){
                lastValue = gd_2048.Data[i][j];
            }else{
                if(lastValue == gd_2048.Data[i][j]){
                    gd_2048.Data[i][currentWritePos] = lastValue*2;
                    gd_2048.Score += lastValue*2;
                    lastValue = 0;
                    if(gd_2048.Data[i][currentWritePos] == Target)
                        gd_2048.Status = S_WIN;
                }else{
                    gd_2048.Data[i][currentWritePos] = lastValue;
                    lastValue = gd_2048.Data[i][j];
                }
                --currentWritePos;
            }
            gd_2048.Data[i][j] = 0;
            if(lastValue) gd_2048.Data[i][currentWritePos] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(gd_2048.Data[i][j] != tmp[i][j]) return 1;
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
            tmp[i][j] = gd_2048.Data[i][j];
            if(!gd_2048.Data[i][j]) continue;
            if(lastValue == 0){
                lastValue = gd_2048.Data[i][j];
            }else{
                if(lastValue == gd_2048.Data[i][j]){
                    gd_2048.Data[currentWritePos][j] = lastValue*2;
                    gd_2048.Score += lastValue*2;
                    lastValue = 0;
                    if(gd_2048.Data[currentWritePos][j] == Target)
                        gd_2048.Status = S_WIN;
                }else{
                    gd_2048.Data[currentWritePos][j] = lastValue;
                    lastValue = gd_2048.Data[i][j];
                }
                ++currentWritePos;
            }
            gd_2048.Data[i][j] = 0;
            if(lastValue) gd_2048.Data[currentWritePos][j] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(gd_2048.Data[i][j] != tmp[i][j]) return 1;
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
            tmp[i][j] = gd_2048.Data[i][j];
            if(!gd_2048.Data[i][j]) continue;
            if(lastValue == 0){
                lastValue = gd_2048.Data[i][j];
            }else{
                if(lastValue == gd_2048.Data[i][j]){
                    gd_2048.Data[currentWritePos][j] = lastValue*2;
                    gd_2048.Score += lastValue*2;
                    lastValue = 0;
                    if(gd_2048.Data[currentWritePos][j] == Target)
                        gd_2048.Status = S_WIN;
                }else{
                    gd_2048.Data[currentWritePos][j] = lastValue;
                    lastValue = gd_2048.Data[i][j];
                }
                --currentWritePos;
            }
            gd_2048.Data[i][j] = 0;
            if(lastValue) gd_2048.Data[currentWritePos][j] = lastValue;
        }
    }
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            if(gd_2048.Data[i][j] != tmp[i][j]) return 1;
    return 0;
}

// 重新开始游戏
void restart(){
    uint8 i, j;
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            gd_2048.Data[i][j] = 0;
    generate_randNum();
    generate_randNum();
    gd_2048.Score = 0;
    gd_2048.Status = S_NORMAL;
}

// 判断游戏结束
uint8 isOver(){
    uint8 i, j;
    for(i=0; i<4; ++i){
        for(j=0; j<4; ++j){
            if(!gd_2048.Data[i][j]) return 0;
            if ((j+1 < 4) && (gd_2048.Data[i][j] == gd_2048.Data[i][j+1]))
                return 0;
            if ((i+1 < 4) && (gd_2048.Data[i][j] == gd_2048.Data[i+1][j]))
                return 0;
        }
    }
    return 1;
}

// 设置测试数据
void setTestData(){
    uint8 i, j;
    int t = 50;
    if(gd_2048.Status != S_NORMAL){
        for(i=0; i<4; ++i)
            for(j=0; j<4; ++j)
                gd_2048.Data[i][j] = 16 << i << j;
        gd_2048.Score = 0;
        gd_2048.Status = S_NORMAL;
        if(gd_2048.Best<0)
            gd_2048.Best = 0;
        updateBuf();
    }
}

// 2048初始化游戏界面
void game_2048_init(){
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

    setTestData();
}

// 处理输入
void game_2048_updateStatus(uint8 key){
    uint8 updated = 0;

    switch(key){
        case 'q':
            gd_2048.Status = S_QUIT;
            break;
        case 'r':
            restart();
            break;
        case 'a':
            if(gd_2048.Status == S_NORMAL) updated = moveLeft();
            break;
        case 'd':
            if(gd_2048.Status == S_NORMAL) updated = moveRight();
            break;
        case 'w':
            if(gd_2048.Status == S_NORMAL) updated = moveUp();
            break;
        case 's':
            if(gd_2048.Status == S_NORMAL) updated = moveDown();
            break;
    }
    
    if(updated){
        generate_randNum();
        if(isOver()) gd_2048.Status = S_FAIL;
        if(gd_2048.Score>gd_2048.Best){
            gd_2048.Best = gd_2048.Score;
            updateBuf();
        }
    }
}

// 运行游戏
void game_2048_run(){
    uint8 buf[50], slen;
    uint8 i, j;
    
    if(gd_2048.Status != S_QUIT){
        // 显示历史最高分、当前得分
        sprintf(buf, "%19d", gd_2048.Best);
        tft_lcd_show_string(68,50,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
        sprintf(buf, "%19d", gd_2048.Score);
        tft_lcd_show_string(68,68,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
        
        // 显示各格内数据
        for(i=0; i<4; ++i){
            for(j=0; j<4; ++j){
                if(gd_2048.Data[i][j]){
                    switch(gd_2048.Data[i][j]){
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
                    sprintf(buf, "%d", (int)gd_2048.Data[i][j]);
                    slen = strlen(buf);
                    tft_lcd_show_string(45+50*j-4*slen,109+50*i,buf,TFT_LCD_WHITE,TFT_LCD_LGRAYBLUE,16,1);
                }else{
                    tft_lcd_fill_rectangle(24+j*50, 96+i*50, 66+j*50, 138+i*50, TFT_LCD_LGRAYBLUE);
                }
            }
        }

        if(gd_2048.Status == S_WIN)
            tft_lcd_show_string(36,300,"          You Win !         ",TFT_LCD_RED,TFT_LCD_LGRAY,12,0);
        else if(gd_2048.Status == S_FAIL)
            tft_lcd_show_string(36,300,"          You Lose!         ",TFT_LCD_RED,TFT_LCD_LGRAY,12,0);
        else
            tft_lcd_show_string(36,300,"Join the tiles, get to 2048!",TFT_LCD_BROWN,TFT_LCD_LGRAY,12,0);
    }
}

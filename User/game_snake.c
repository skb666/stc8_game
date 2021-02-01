#include "game.h"

// 贪吃蛇游戏数据
gameData_snake gd_snake;

uint8 isOnSnake(Axis *elem, Snake snake){
    Node *ptr = snake;
    while(ptr){
        if((elem->x == ptr->axis.x) && (elem->y == ptr->axis.y))
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

void destroye_snake(){
    Node *ptr = gd_snake.snake;
    while(ptr){
        gd_snake.snake = gd_snake.snake->next;
        free(ptr);
        ptr = gd_snake.snake;
    }
}

void generate_snake(){
    Node *ptr;
    gd_snake.length = 2;
    gd_snake.snake = (Snake)malloc(sizeof(Node));
    gd_snake.snake->axis.x = rand()%10 + 5;
    gd_snake.snake->axis.y = rand()%10 + 5;
    ptr = (Node *)malloc(sizeof(Node));
    ptr->next = NULL;
    switch(rand()%4){
        case 0:
            gd_snake.direction = D_UP;
            ptr->axis.x = gd_snake.snake->axis.x;
            ptr->axis.y = gd_snake.snake->axis.y + 1;
            break;
        case 1:
            gd_snake.direction = D_DOWN;
            ptr->axis.x = gd_snake.snake->axis.x;
            ptr->axis.y = gd_snake.snake->axis.y - 1;
            break;
        case 2:
            gd_snake.direction = D_LEFT;
            ptr->axis.x = gd_snake.snake->axis.x + 1;
            ptr->axis.y = gd_snake.snake->axis.y;
            break;
        case 3:
            gd_snake.direction = D_RIGHT;
            ptr->axis.x = gd_snake.snake->axis.x - 1;
            ptr->axis.y = gd_snake.snake->axis.y;
            break;
    }
    gd_snake.snake->next = ptr;
}

void generate_food(){
    do{
        gd_snake.food.x = rand()%20;
        gd_snake.food.y = rand()%20;
    }while(isOnSnake(&gd_snake.food, gd_snake.snake));
}

// 设置数据
void setData_snake(){
    uint8 t = 0;
    gd_snake.Score = 0;
    gd_snake.Status = S_PAUSE;
    generate_snake();
    generate_food();
    if(gd_snake.Best<0){
        gd_snake.Best = 0;
        t = 1;
    }
    if(gd_snake.Speed < 0 || gd_snake.Speed > 3){
        gd_snake.Speed = SPEED_MEDIUM;
        t = 1;
    }
    if(t) updateFromBuf();
}

// 贪吃蛇初始化游戏界面
void game_snake_init(){
    uint8 i;
    tft_lcd_clear(TFT_LCD_LGRAY);
    tft_lcd_show_font32(3,str_snake,72,8,TFT_LCD_BLUE,TFT_LCD_WHITE,1);
    tft_lcd_draw_rectangle(19, 91, 221, 293, TFT_LCD_BLACK);
    tft_lcd_fill_rectangle(20, 92, 220, 292, TFT_LCD_LGRAYBLUE);
    tft_lcd_show_string(20,50,"Best :",TFT_LCD_BLACK,TFT_LCD_LGRAY,16,1);
    tft_lcd_show_string(20,68,"Score:",TFT_LCD_BLACK,TFT_LCD_LGRAY,16,1);
    tft_lcd_fill_rectangle(158, 50, 220, 84, TFT_LCD_LGRAYBLUE);
    tft_lcd_draw_line(162, 65, 216, 65, TFT_LCD_GRAY);
    tft_lcd_show_string(174,52,"Speed",TFT_LCD_BLACK,TFT_LCD_LGRAYBLUE,12,1);
    for(i=0; i<21; ++i){
        tft_lcd_draw_line(20, 92+10*i, 220, 92+10*i, TFT_LCD_LIGHTBLUE);
        tft_lcd_draw_line(20+10*i, 92, 20+10*i, 292, TFT_LCD_LIGHTBLUE);
    }
    // 设置数据
    setData_snake();
}

// 运行游戏
void game_snake_run(){
    uint8 buf[25];
    Node *ptr = gd_snake.snake->next;
    
    if(gd_snake.Status != S_QUIT){
        // 显示速度
        switch(gd_snake.Speed){
            case SPEED_MEDIUM:
                tft_lcd_show_string(165,67,"medium",TFT_LCD_BROWN,TFT_LCD_LGRAYBLUE,16,0);
                break;
            case SPEED_SLOW:
                tft_lcd_show_string(165,67," slow ",TFT_LCD_YELLOW,TFT_LCD_LGRAYBLUE,16,0);
                break;
            case SPEED_FAST:
                tft_lcd_show_string(165,67," fast ",TFT_LCD_BRRED,TFT_LCD_LGRAYBLUE,16,0);
                break;
        }
        
        // 显示历史最高分、当前得分
        sprintf(buf, "%8d", (int)ptr->axis.x);
        tft_lcd_show_string(68,50,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
        sprintf(buf, "%8d", (int)ptr->axis.y);
        tft_lcd_show_string(68,68,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
        
        // 画食物
        tft_lcd_fill_rectangle( 21+10*gd_snake.food.x, 93+10*gd_snake.food.y,
                                29+10*gd_snake.food.x, 101+10*gd_snake.food.y,
                                TFT_LCD_GREEN);
        // 画蛇头
        tft_lcd_fill_rectangle( 21+10*gd_snake.snake->axis.x, 93+10*gd_snake.snake->axis.y,
                                29+10*gd_snake.snake->axis.x, 101+10*gd_snake.snake->axis.y,
                                TFT_LCD_BLUE);
        // 画蛇身
        while(ptr){
            tft_lcd_fill_rectangle( 21+10*ptr->axis.x, 93+10*ptr->axis.y,
                                    29+10*ptr->axis.x, 101+10*ptr->axis.y,
                                    TFT_LCD_DARKBLUE);                                                                                                                                                                                                            
            ptr = ptr->next;
        }
        
        switch(gd_snake.Status){
            case S_WIN:
                tft_lcd_show_string(36,300,"          You Win !         ",TFT_LCD_RED,TFT_LCD_LGRAY,12,0);
                break;
            case S_FAIL:
                tft_lcd_show_string(36,300,"         Game Over !        ",TFT_LCD_RED,TFT_LCD_LGRAY,12,0);
                break;
            case S_PAUSE:
                tft_lcd_show_string(36,300,"           Pause            ",TFT_LCD_RED,TFT_LCD_LGRAY,12,0);
                break;
            case S_NORMAL:
                tft_lcd_show_string(36,300,"           Normal           ",TFT_LCD_BROWN,TFT_LCD_LGRAY,12,0);
                break;
        }
    }
}

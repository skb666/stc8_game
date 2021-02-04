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

void generate_snake(){
    Node *ptr;
    gd_snake.length = 2;
    gd_snake.snake = (Snake)malloc(sizeof(Node));
    gd_snake.snake->pre = NULL;
    gd_snake.snake->axis.x = rand()%10 + 5;
    gd_snake.snake->axis.y = rand()%10 + 5;
    ptr = (Node *)malloc(sizeof(Node));
    ptr->pre = gd_snake.snake;
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
    gd_snake.snake_tail = ptr;
}

void generate_food(){
    do{
        gd_snake.food.x = rand()%20;
        gd_snake.food.y = rand()%20;
    }while(isOnSnake(&gd_snake.food, gd_snake.snake));
}

uint8 isOver_snake(){
    // 撞身体
    if(gd_snake.length > 3)
        if(isOnSnake(&gd_snake.snake->axis, gd_snake.snake->next->next))
            return 1;
    // 撞墙
    if((gd_snake.snake->axis.x < 0) || (gd_snake.snake->axis.x > 19))
        return 1;
    if((gd_snake.snake->axis.y < 0) || (gd_snake.snake->axis.y > 19))
        return 1;
    return 0;
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

void draw_snake_speed(){
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
}

void draw_snake_score(){
    uint8 buf[25];
    // 显示历史最高分、当前得分
    sprintf(buf, "%8d", gd_snake.Best);
    tft_lcd_show_string(68,50,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
    sprintf(buf, "%8d", gd_snake.Score);
    tft_lcd_show_string(68,68,buf,TFT_LCD_LBBLUE,TFT_LCD_LGRAY,16,0);
}

void draw_snake_status(){
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

void draw_snake_axis(Axis *axis, uint16 color){
    tft_lcd_fill_rectangle( 21+10*axis->x, 93+10*axis->y,
                            29+10*axis->x, 101+10*axis->y,
                            color);
}

void draw_snake_main(){
    Node *ptr = gd_snake.snake->next;
    
    // 画食物
    tft_lcd_fill_rectangle( 21+10*gd_snake.food.x, 93+10*gd_snake.food.y,
                            29+10*gd_snake.food.x, 101+10*gd_snake.food.y,
                            TFT_LCD_GREEN);
    // 画蛇头
    if( (gd_snake.snake->axis.x >= 0) && (gd_snake.snake->axis.x < 20) && 
        (gd_snake.snake->axis.y >= 0) && (gd_snake.snake->axis.y < 20))
        tft_lcd_fill_rectangle( 21+10*gd_snake.snake->axis.x, 93+10*gd_snake.snake->axis.y,
                                29+10*gd_snake.snake->axis.x, 101+10*gd_snake.snake->axis.y,
                                TFT_LCD_DARKBLUE);
    // 画蛇身
    while(ptr){
        tft_lcd_fill_rectangle( 21+10*ptr->axis.x, 93+10*ptr->axis.y,
                                29+10*ptr->axis.x, 101+10*ptr->axis.y,
                                TFT_LCD_GRAYBLUE);                                                                                                                                                                                                            
        ptr = ptr->next;
    }
}

void snakeMove(){
    Node *ptr;
    if(gd_snake.Status == S_NORMAL){
        // 创建新蛇头
        ptr = (Snake)malloc(sizeof(Node));
        ptr->pre = NULL;
        switch(gd_snake.direction){
            case D_UP:
                ptr->axis.x = gd_snake.snake->axis.x;
                ptr->axis.y = gd_snake.snake->axis.y - 1;
                break;
            case D_DOWN:
                ptr->axis.x = gd_snake.snake->axis.x;
                ptr->axis.y = gd_snake.snake->axis.y + 1;
                break;
            case D_LEFT:
                ptr->axis.x = gd_snake.snake->axis.x - 1;
                ptr->axis.y = gd_snake.snake->axis.y;
                break;
            case D_RIGHT:
                ptr->axis.x = gd_snake.snake->axis.x + 1;
                ptr->axis.y = gd_snake.snake->axis.y;
                break;
        }
        gd_snake.snake->pre = ptr;
        ptr->next = gd_snake.snake;
        gd_snake.snake = ptr;
        
        // 判断是否吃到食物
        if((ptr->axis.x == gd_snake.food.x) && (ptr->axis.y == gd_snake.food.y)){
            if(++gd_snake.length == 400){
                gd_snake.Status = S_WIN;
                draw_snake_status();
            }else{
                generate_food();
                draw_snake_axis(&gd_snake.food, TFT_LCD_GREEN);
            }
            // 更新得分
            gd_snake.Score += 10;
            if(gd_snake.Score > gd_snake.Best){
                gd_snake.Best = gd_snake.Score;
                updateFromBuf();
            }
            draw_snake_score();
        }else{
            // 去尾
            draw_snake_axis(&gd_snake.snake_tail->axis, TFT_LCD_LGRAYBLUE);         // 旧蛇尾消去
            ptr = gd_snake.snake_tail;
            gd_snake.snake_tail->pre->next = NULL;
            gd_snake.snake_tail = gd_snake.snake_tail->pre;
            free(ptr);
        }
        draw_snake_axis(&gd_snake.snake->next->axis, TFT_LCD_GRAYBLUE);             // 旧蛇头变蛇身
        
        // isOver?
        if(isOver_snake()){
            gd_snake.Status = S_FAIL;
            draw_snake_status();
        }else{
            draw_snake_axis(&gd_snake.snake->axis, TFT_LCD_DARKBLUE);               // 新蛇头
        }
    }
}

void destroye_snake(){
    Node *ptr = gd_snake.snake;
    while(ptr){
        if( (ptr->axis.x >= 0) && (ptr->axis.x < 20) && 
            (ptr->axis.y >= 0) && (ptr->axis.y < 20))
            draw_snake_axis(&ptr->axis, TFT_LCD_LGRAYBLUE);
        gd_snake.snake = gd_snake.snake->next;
        free(ptr);
        ptr = gd_snake.snake;
    }
    gd_snake.snake_tail = NULL;
}

void destroye_food(){
    draw_snake_axis(&gd_snake.food, TFT_LCD_LGRAYBLUE);
}

void restart_snake(){
    gd_snake.Score = 0;
    destroye_snake();
    generate_snake();
    destroye_food();
    generate_food();
    gd_snake.Status = S_NORMAL;
    draw_snake_score();
    draw_snake_main();
    draw_snake_status();
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
    draw_snake_speed();
    draw_snake_score();
    draw_snake_main();
    draw_snake_status();
}

// 处理输入
void game_snake_updateStatus(uint8 key){
    switch(key){
        case 'q':
            // TODO
            break;
        case 'r':
            restart_snake();
            break;
        case 'a':
            if(gd_snake.Status == S_NORMAL)
                if((gd_snake.direction == D_UP) || (gd_snake.direction == D_DOWN))
                    gd_snake.direction = D_LEFT;
            break;
        case 'd':
            if(gd_snake.Status == S_NORMAL)
                if((gd_snake.direction == D_UP) || (gd_snake.direction == D_DOWN))
                    gd_snake.direction = D_RIGHT;
            break;
        case 'w':
            if(gd_snake.Status == S_NORMAL)
                if((gd_snake.direction == D_LEFT) || (gd_snake.direction == D_RIGHT))
                    gd_snake.direction = D_UP;
            break;
        case 's':
            if(gd_snake.Status == S_NORMAL)
                if((gd_snake.direction == D_LEFT) || (gd_snake.direction == D_RIGHT))
                    gd_snake.direction = D_DOWN;
            break;
        case 'c':
            if(gd_snake.Status == S_NORMAL){
                gd_snake.Status = S_PAUSE;
                draw_snake_status();
            }else if(gd_snake.Status == S_PAUSE){
                gd_snake.Status = S_NORMAL;
                draw_snake_status();
            }else if(gd_snake.Status == S_WIN || gd_snake.Status == S_FAIL){
                restart_snake();
            }
            break;
        case SPEED_SLOW:
            gd_snake.Speed = SPEED_SLOW;
            draw_snake_speed();
            updateFromBuf();
            break;
        case SPEED_MEDIUM:
            gd_snake.Speed = SPEED_MEDIUM;
            draw_snake_speed();
            updateFromBuf();
            break;
        case SPEED_FAST:
            gd_snake.Speed = SPEED_FAST;
            draw_snake_speed();
            updateFromBuf();
            break;
    }
}

void gSnake_check_key(){
    if(buf_l != buf_r){
        if(key_buf[buf_l].type == K_IR){
            switch(key_buf[buf_l].value){
                case 17:
                    game_snake_updateStatus('w');
                    break;
                case 25:
                    game_snake_updateStatus('s');
                    break;
                case 20:
                    game_snake_updateStatus('a');
                    break;
                case 22:
                    game_snake_updateStatus('d');
                    break;
                case 12:
                    game_snake_updateStatus('q');
                    break;
                case 14:
                    game_snake_updateStatus('r');
                    break;
                case 21:
                    game_snake_updateStatus('c');
                    break;
                case 4:
                    game_snake_updateStatus(SPEED_SLOW);
                    break;
                case 5:
                    game_snake_updateStatus(SPEED_MEDIUM);
                    break;
                case 6:
                    game_snake_updateStatus(SPEED_FAST);
                    break;
            }
        }else if(key_buf[buf_l].type == K_KBD){
            switch(key_buf[buf_l].value){
                case '+':
                    game_snake_updateStatus('w');
                    break;
                case '/':
                    game_snake_updateStatus('s');
                    break;
                case '-':
                    game_snake_updateStatus('a');
                    break;
                case 'x':
                    game_snake_updateStatus('d');
                    break;
                case '*':
                    game_snake_updateStatus('q');
                    break;
                case '#':
                    game_snake_updateStatus('r');
                    break;
                case 0:
                    game_snake_updateStatus('c');
                    break;
                case 4:
                    game_snake_updateStatus(SPEED_SLOW);
                    break;
                case 5:
                    game_snake_updateStatus(SPEED_MEDIUM);
                    break;
                case 6:
                    game_snake_updateStatus(SPEED_FAST);
                    break;
            }
        }
        ++buf_l;
    }else{
        clear_key_buf();
    }
}

// 运行游戏
void game_snake_run(){
    static uint8 cnt = 0;
    if(B_50ms){
        B_50ms = 0;
        switch(gd_snake.Speed){
            case SPEED_SLOW:
                if(++cnt >= 10){
                    cnt = 0;
                    gSnake_check_key();
                    snakeMove();
                }
                break;
            case SPEED_MEDIUM:
                if(++cnt >= 6){
                    cnt = 0;
                    gSnake_check_key();
                    snakeMove();
                }
                break;
            case SPEED_FAST:
                if(++cnt >= 3){
                    cnt = 0;
                    gSnake_check_key();
                    snakeMove();
                }
                break;
        }
    }
}

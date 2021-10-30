#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>

using namespace std;

int window_w = 800;
int window_h = 600;

typedef pair<int,int> pii;

struct PT
{
    int x, y;
    PT() {}
    PT(int a, int b)
    {
        x = a;
        y = b;
    }
};

pii shift_pixel(int x, int y)
{
    x += window_w/2;
    y = -y;
    y += window_h/2;

    return make_pair(x, y);
}

void draw_pixel(int x, int y, int color)
{
    pii p = shift_pixel(x, y);
    putpixel(p.first, p.second, color);
}

void draw_axis()
{
    for(int i = -(window_w/2); i<=window_w/2; i++)
    {
        draw_pixel(i, 0, WHITE);
    }
    for(int i = -(window_h/2); i<=window_h/2; i++)
    {
        draw_pixel(0, i, WHITE);
    }
}

void Bressenham(int h, int k , int r, int color)
{
    cout<<"######Bressenham Circle Drawing#####"<<endl;
    int x = 0, y = r;
    int d_not = 3 - 2 * r;

    while(y >= x)
    {
        delay(1);
        draw_pixel(h+x, k+y, color);
        draw_pixel(h-x, k+y, color);
        draw_pixel(h+x, k-y, color);
        draw_pixel(h-x, k-y, color);
        draw_pixel(h+y, k+x, color);
        draw_pixel(h-y, k+x, color);
        draw_pixel(h+y, k-x, color);
        draw_pixel(h-y, k-x, color);

        if(d_not>0)
        {
            y--;
            d_not = d_not + 4 * (x - y) + 10;
        }
        else
        {
            d_not = d_not + (4 * x) + 6;
        }
        x++;
    }
}

void Midpoint(int h, int k, int r, int color)
{
    cout<<"#####Midpoint Circle Drawing#####"<<endl;
    int x = 0, y = r;
    double d_not = (5.0/4.0) - r;

    draw_pixel(h+x, k+y, color);
    draw_pixel(h+y, k+x, color);
    draw_pixel(h+x, k-y, color);
    draw_pixel(h-y, k+x, color);
    while(y>=x)
    {
        if(d_not>0)
        {
            d_not = d_not + 2 * x - 2 * y + 5;

            delay(1);
            draw_pixel(h+x+1, k+y-1, color);
            draw_pixel(h+y-1, k+x+1, color);
            draw_pixel(h+y-1, k-x-1, color);
            draw_pixel(h+x+1, k-y+1, color);
            draw_pixel(h-x-1, k-y+1, color);
            draw_pixel(h-y+1, k-x-1, color);
            draw_pixel(h-y+1, k+x+1, color);
            draw_pixel(h-x-1, k+y-1, color);
            y--;
        }
        else
        {
            d_not = d_not + 2 * x + 3;

            delay(1);
            draw_pixel(h+x+1, k+y, color);
            draw_pixel(h+y, k+x+1, color);
            draw_pixel(h+y, k-x-1, color);
            draw_pixel(h+x+1, k-y, color);
            draw_pixel(h-x-1, k-y, color);
            draw_pixel(h-y, k-x-1, color);
            draw_pixel(h-y, k+x+1, color);
            draw_pixel(h-x-1, k+y, color);
        }
        x++;
    }
}

using namespace std;

int main()
{
    initwindow(window_w,window_h);
    draw_axis();

    int c;
    cout<<"Enter (1) for Bressenham Circle Drawing\nEnter (2) for Midpoint Circle Drawing\nEnter (3) for both(overlap)"<<endl;
    cin>>c;
    int h, k, r;
    cout<<"("<<-window_w/2<<"<= x <="<<window_w/2<<")"<<endl;
    cout<<"("<<-window_h/2<<"<= y <="<<window_h/2<<")"<<endl;
    cout<<"Enter Center: "<<endl;
    cout<<"h: ";
    cin>>h;
    cout<<"k: ";
    cin>>k;
    cout<<"Radius r: ";
    cin>>r;

    switch(c)
    {
    case 1:
        Bressenham(h, k, r, YELLOW);
        break;
    case 2:
        Midpoint(h, k, r, YELLOW);
        break;
    case 3:
        Bressenham(h, k, r, YELLOW);
        Midpoint(h, k, r, GREEN);
        break;
    default:
        cout<<"Incorrect Selection."<<endl;
        break;

    }

    system("pause");
    return 0;
}

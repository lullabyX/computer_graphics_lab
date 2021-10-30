#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>

using namespace std;

int window_w = 800;
int window_h = 600;

typedef pair<int,int> pii;

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

void DDA(int x1, int x2, int y1, int y2, int color)
{
    cout<<"#####Direct Differential Line Drawing#####"<<endl;

    if(y1 == y2 | x1 == x2)
    {
        if(y1 == y2)
        {
            cout<<"Horizontal"<<endl;
            if(x1>x2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            while(x1 != x2)
            {
                delay(1);
                draw_pixel(x1++, y1, color);
            }

        }
        else
        {
            cout<<"Vertical"<<endl;
            if(y1>y2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            while(y1 != y2)
            {
                delay(1);
                draw_pixel(x1, y1++, color);
            }

        }
    }
    else
    {
        float m = (float)(y2-y1)/(float)(x2-x1);
        cout<<"Slope: "<<m<<endl;

        if(m>1 | m<-1)
        {
            if(y1>y2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            float x = x1;
            while(y1 <= y2)
            {
                delay(1);
                draw_pixel(round(x), y1++, color);
                x += (1/m);
            }
        }
        else
        {
            if(x1>x2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            float y = y1;
            while(x1 <= x2)
            {
                delay(1);
                draw_pixel(x1++, round(y), color);
                y += m;
            }
        }
    }
}

void Bressenham(int x1, int x2, int y1, int y2, int color)
{
    cout<<"#####Bressenham Line Drawing#####"<<endl;
    if((x1!=x2) && (y1!=y2))
    {
        if(y1>y2)
        {
            swap(y1, y2);
            swap(x1, x2);
        }
        int dy = y2 - y1;
        int dx = x2 - x1;
        float m = (float)dy/(float)dx;
        cout<<"Slope: "<<m<<endl;
        if(0<m && m<=1)
        {
            int d_not = (2*dy) - dx;
            int d_k = d_not;
            draw_pixel(x1, y1, color);
            while(x1<x2)
            {
                if(d_k>=0)
                {
                    d_k += 2*(dy-dx);
                    y1++;
                }
                else
                {
                    d_k += 2*dy;
                }
                delay(1);
                draw_pixel(++x1, y1, color);
            }
        }
        else if(-1<=m && m<0)
        {
            dx = -dx;
            int d_not = (2*dy) - dx;
            int d_k = d_not;
            draw_pixel(x1, y1, color);
            while(x2<x1)
            {
                if(d_k>=0)
                {
                    d_k += 2*(dy-dx);
                    y1++;
                }
                else
                {
                    d_k += 2*dy;
                }
                delay(1);
                draw_pixel(--x1, y1, color);
            }
        }
        else if(m>1)
        {
            int d_not = (2*dx) - dy;
            int d_k = d_not;
            draw_pixel(x1, y1, color);
            while(y1<y2)
            {
                if(d_k>=0)
                {
                    d_k += 2*(dx-dy);
                    x1++;
                }
                else
                {
                    d_k += 2*dx;
                }
                delay(1);
                draw_pixel(x1, ++y1, color);
            }
        }
        else if(m<-1)
        {
            dx = -dx;
            int d_not = (2*dx) - dy;
            int d_k = d_not;
            draw_pixel(x1, y1, color);
            while(y1<y2)
            {
                if(d_k>=0)
                {
                    d_k += 2*(dx-dy);
                    x1--;
                }
                else
                {
                    d_k += 2*dx;
                }
                delay(1);
                draw_pixel(x1, ++y1, color);
            }
        }
    }
    else if(y1 == y2)
    {
        if(x1>x2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }
        while(x1 != x2)
        {
            delay(1);
            draw_pixel(x1++, y1, color);
        }
    }
    else
    {
        if(y1>y2)
        {
            swap(y1, y2);
            swap(x1, x2);
        }
        while(y1 != y2)
        {
            delay(1);
            draw_pixel(x1, y1++, color);
        }
    }
}

int main()
{
    initwindow(window_w,window_h);
    draw_axis();

    int c;
    cout<<"Enter (1) for Bressenham Line Drawing\nEnter (2) for DDA Line Drawing\nEnter (3) for both(overlap)"<<endl;
    cin>>c;
    int x1, x2, y1, y2;
    cout<<"("<<-window_w/2<<"<= x <="<<window_w/2<<")"<<endl;
    cout<<"("<<-window_h/2<<"<= y <="<<window_h/2<<")"<<endl;
    cout<<"Enter Coordinates: "<<endl;
    cout<<"x1: ";
    cin>>x1;
    cout<<"y1: ";
    cin>>y1;
    cout<<"x2: ";
    cin>>x2;
    cout<<"y2: ";
    cin>>y2;

    switch(c)
    {
    case 1:
        Bressenham(x1, x2, y1, y2, YELLOW);
        break;
    case 2:
        DDA(x1, x2, y1, y2, YELLOW);
        break;
    case 3:
        Bressenham(x1, x2, y1, y2, YELLOW);
        DDA(x1, x2, y1, y2, GREEN);
        break;
    default:
        cout<<"Incorrect Selection."<<endl;
        break;

    }



    system("pause");

    return 0;
}

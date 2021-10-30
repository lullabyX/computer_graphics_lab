#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>

using namespace std;

int window_w = 800;
int window_h = 600;
int axisColor = 15;

typedef pair<int,int> pii;

struct PT
{
    int x, y;
    PT() {};
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
        draw_pixel(i, 0, axisColor);
    }
    for(int i = -(window_h/2); i<=window_h/2; i++)
    {
        draw_pixel(0, i, axisColor);
    }
}

void Bressenham(PT A, PT B)
{
    int x1 = A.x;
    int x2 = B.x;
    int y1 = A.y;
    int y2 = B.y;

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
//        cout<<"Slope: "<<m<<endl;
        if(0<m && m<=1)
        {
            int d_not = (2*dy) - dx;
            int d_k = d_not;
            draw_pixel(x1, y1, YELLOW);
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
                //delay(.9);
                draw_pixel(++x1, y1, YELLOW);
            }
        }
        else if(-1<=m && m<0)
        {
            dx = -dx;
            int d_not = (2*dy) - dx;
            int d_k = d_not;
            draw_pixel(x1, y1, YELLOW);
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
                //delay(.9);
                draw_pixel(--x1, y1, YELLOW);
            }
        }
        else if(m>1)
        {
            int d_not = (2*dx) - dy;
            int d_k = d_not;
            draw_pixel(x1, y1, YELLOW);
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
                //delay(.9);
                draw_pixel(x1, ++y1, YELLOW);
            }
        }
        else if(m<-1)
        {
            dx = -dx;
            int d_not = (2*dx) - dy;
            int d_k = d_not;
            draw_pixel(x1, y1, YELLOW);
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
                //delay(.9);
                draw_pixel(x1, ++y1, YELLOW);
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
        while(x1 <= x2)
        {
            //delay(.9);
            draw_pixel(x1++, y1, YELLOW);
        }
    }
    else
    {
        if(y1>y2)
        {
            swap(y1, y2);
            swap(x1, x2);
        }
        while(y1 <= y2)
        {
            //delay(.9);
            draw_pixel(x1, y1++, YELLOW);
        }
    }
}

void draw_polygon(vector<PT> points)
{
    int n = points.size();
    for(int i = 0; i<n; i++)
    {
        Bressenham(points[i], points[(i+1)%n]);
    }
}

void BoundaryFill(PT currPixel, int boundaryColor, int fillColor)
{
    pii pixel = shift_pixel(currPixel.x, currPixel.y);
    int currColor = getpixel(pixel.first, pixel.second);
    if(currColor == boundaryColor || currColor == fillColor)
    {
        return;
    }

    draw_pixel(currPixel.x, currPixel.y, fillColor);

    BoundaryFill(PT(currPixel.x, currPixel.y+1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x, currPixel.y-1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x+1, currPixel.y), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x-1, currPixel.y), boundaryColor, fillColor);
}

void FloodFill(PT currPixel, int backgroudColor, int fillColor)
{
    pii pixel = shift_pixel(currPixel.x, currPixel.y);
    int currColor = getpixel(pixel.first, pixel.second);
    if(currColor != axisColor && currColor != backgroudColor)
    {
        return;
    }

    draw_pixel(currPixel.x, currPixel.y, fillColor);

    FloodFill(PT(currPixel.x, currPixel.y+1), backgroudColor, fillColor);
    FloodFill(PT(currPixel.x, currPixel.y-1), backgroudColor, fillColor);
    FloodFill(PT(currPixel.x+1, currPixel.y), backgroudColor, fillColor);
    FloodFill(PT(currPixel.x-1, currPixel.y), backgroudColor, fillColor);
}

int main()
{
    initwindow(window_w, window_h);
    int backgroundColor = getpixel(0,0);
    draw_axis();

    int c;
    cout<<"Enter (1) for Flood Fill\nEnter (2) for Boundary Fill"<<endl;
    cin>>c;

    vector<PT> points;

// scaled up polygon, throws memory unaccessable error

//    points.push_back(PT(-100, -100));
//    points.push_back(PT(-50, -125));
//    points.push_back(PT(50, -50));
//    points.push_back(PT(100, -125));
//    points.push_back(PT(200, -50));
//    points.push_back(PT(200, 100));
//    points.push_back(PT(0, 150));
//    points.push_back(PT(-100, 50));
//    points.push_back(PT(-200, 50));

    points.push_back(PT(-50, -50));
    points.push_back(PT(-25, -60));
    points.push_back(PT(10, -10));
    points.push_back(PT(50, -60));
    points.push_back(PT(100, -25));
    points.push_back(PT(100, 50));
    points.push_back(PT(0, 75));
    points.push_back(PT(-50, 25));
    points.push_back(PT(-100, 25));

// large rectangle

//    points.push_back(PT(-300, -200));
//    points.push_back(PT(300, -200));
//    points.push_back(PT(300, 200));
//    points.push_back(PT(-300, 200));


//small rectangle

//    points.push_back(PT(-100, -100));
//    points.push_back(PT(100, -100));
//    points.push_back(PT(100, 100));
//    points.push_back(PT(-100, 100));

    draw_polygon(points);
    switch(c)
    {
    case 1:

        cout<<"Flood Fill: "<<endl;
        FloodFill(PT(0,0), backgroundColor, GREEN);
        break;
    case 2:
        cout<<"Boundary Fill: "<<endl;
        BoundaryFill(PT(0,0), YELLOW, GREEN);
        break;
    default:
        cout<<"Incorrect Selection."<<endl;
        break;

    }

    system("pause");

    return 0;
}


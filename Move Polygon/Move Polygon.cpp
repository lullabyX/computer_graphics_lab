#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include <Windows.h>

using namespace std;

int window_w = 800;
int window_h = 600;
int axisColor = 15;
int backgroundColor;

typedef pair<int,int> pii;

struct PT
{
    double x, y;
    PT() {};
    PT(double a, double b)
    {
        x = a;
        y = b;
    }

    bool operator < (const PT &p)const
    {
        return x < p.x;
    }
};

#define AS PT (-60, 18)
#define BS PT (-12, 18)
#define CS PT (0, 60)
#define DS PT (12, 18)
#define ES PT (60, 18)
#define FS PT (22, -6)
#define GS PT (38, -50)
#define HS PT (0, -24)
#define IS PT (-38, -50)
#define JS PT (-22, -6)

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

void Bressenham(PT A, PT B, int color)
{
    int x1 = round(A.x);
    int x2 = round(B.x);
    int y1 = round(A.y);
    int y2 = round(B.y);

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
                //delay(.9);
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
                //delay(.9);
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
                //delay(.9);
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
                //delay(.9);
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
        while(x1 <= x2)
        {
            //delay(.9);
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
        while(y1 <= y2)
        {
            //delay(.9);
            draw_pixel(x1, y1++, color);
        }
    }
}

void draw_polygon(vector<PT> points, int color)
{
    int n = points.size();
    for(int i = 0; i<n; i++)
    {
        Bressenham(points[i], points[(i+1)%n], color);
    }
}

struct EDGE
{
    double y_min, y_max, x_with_y_min, m_inv;
    EDGE() {};
    EDGE(double ymin, double ymax, double xwith_y_min, double minv)
    {
        y_min = ymin;
        y_max = ymax;
        x_with_y_min = xwith_y_min;
        m_inv = minv;
    }

    bool operator < (const EDGE &e)const
    {
        return y_min < e.y_min;
    }
};

void Scanline(vector<PT> points, int color, int borderColor)
{
    vector<EDGE> edges;

    int n = points.size();
    double st = DBL_MAX;
    double fin = DBL_MIN;

    map<double, int>mp;

    for(int i = 0; i<n; i++)
    {
        PT p1 = points[i];
        PT p2 = points[(i+1)%n];

        if(p1.y == p2.y)
        {
            continue;
        }
        EDGE tmp;
        tmp.y_min = min(p1.y, p2.y);
        tmp.y_max = max(p1.y, p2.y);
        tmp.x_with_y_min = p1.y < p2.y ? p1.x : p2.x;
        tmp.m_inv = (p2.x - p1.x)/(p2.y - p1.y);

        mp[tmp.y_min] = 1;
        st = min(st, tmp.y_min);
        fin = max(fin, tmp.y_max);

        edges.push_back(tmp);
    }

    sort(edges.begin(), edges.end());

    for(int i = 0; i<edges.size(); i++)
    {
        if(mp[edges[i].y_max] == 1)
        {
            edges[i].y_max--;
        }
    }


    for(int y = st; y <= fin; y++)
    {
        vector<PT> intersects;
        for(int i = 0; i < edges.size(); i++)
        {
            if(y >= edges[i].y_min && y <= edges[i].y_max)
            {
                intersects.push_back(PT(edges[i].x_with_y_min, y));
                edges[i].x_with_y_min += edges[i].m_inv;
            }
        }
        sort(intersects.begin(), intersects.end());

        for(int i = 0; i<intersects.size()-1; i+=2)
        {
//            pii pixel1 = shift_pixel(intersects[i].x, intersects[i].y);
//            pii pixel2 = shift_pixel(intersects[i+1].x, intersects[i+1].y);
//
//            if(intersects[i].x < intersects[i+1].x)
//            {
//                if((getpixel(pixel1.first, pixel1.second)==borderColor))
//                    intersects[i].x += 1;
//                if((getpixel(pixel2.first, pixel2.second)==borderColor))
//                    intersects[i+1].x -= 1;
//                pixel1 = shift_pixel(intersects[i].x, intersects[i].y);
//                pixel2 = shift_pixel(intersects[i+1].x, intersects[i+1].y);
//                if((getpixel(pixel1.first, pixel1.second)==borderColor))
//                    intersects[i].x += 1;
//                if((getpixel(pixel2.first, pixel2.second)==borderColor))
//                    intersects[i+1].x -= 1;
//            }
//            else
//            {
//                if((getpixel(pixel1.first, pixel1.second)==borderColor))
//                    intersects[i].x -= 1;
//                if((getpixel(pixel2.first, pixel2.second)==borderColor))
//                    intersects[i+1].x += 1;
//                pixel1 = shift_pixel(intersects[i].x, intersects[i].y);
//                pixel2 = shift_pixel(intersects[i+1].x, intersects[i+1].y);
//                if((getpixel(pixel1.first, pixel1.second)==borderColor))
//                    intersects[i].x -= 1;
//                if((getpixel(pixel2.first, pixel2.second)==borderColor))
//                    intersects[i+1].x += 1;
//            }

            Bressenham(intersects[i], intersects[i+1], color);
        }
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

int main()
{
    initwindow(window_w, window_h);
    backgroundColor = getpixel(0,0);
    //draw_axis();

    vector<PT> points;

    points.push_back(AS);
    points.push_back(BS);
    points.push_back(CS);
    points.push_back(DS);
    points.push_back(ES);
    points.push_back(FS);
    points.push_back(GS);
    points.push_back(HS);
    points.push_back(IS);
    points.push_back(JS);


//Scaled down version

//    points.push_back(PT(-50, -50));
//    points.push_back(PT(-25, -60));
//    points.push_back(PT(10, -10));
//    points.push_back(PT(50, -60));
//    points.push_back(PT(100, -25));
//    points.push_back(PT(100, 50));
//    points.push_back(PT(0, 75));
//    points.push_back(PT(-50, 25));
//    points.push_back(PT(-100, 25));

//Rectangle coordinates

//    points.push_back(PT(-300, -200));
//    points.push_back(PT(300, -200));
//    points.push_back(PT(300, 200));
//    points.push_back(PT(-300, 200));

    int x, y;
    x = y = 0;
    int mx, my;
    bool flag = false;

    getmouseclick(WM_LBUTTONDOWN, mx, my);
        if(mx != -1 && my != -1)
        {
//            pii pixel = shift_pixel(mx, my);
//            cout<<mx<<" mouse "<<my<<endl;
//            cout<<pixel.first<<" Pixel "<<pixel.second<<endl;
            int r = mx;
            int l = mx;
            while(r<(window_w))
            {
                if(getpixel(r, my)==YELLOW)
                    break;
                r++;
            }
            while(l>0)
            {
                if(getpixel(l, my)==YELLOW)
                    break;
                l--;
            }
            if(r!=(window_w) && l!=0)
            {
                cout<<"Mouse clicked inside the star!"<<endl;
                flag = !flag;
                if(flag)
                    BoundaryFill(PT(points[2].x, points[2].y-10), YELLOW, GREEN);
                else
                {
                    cleardevice();
                    draw_polygon(points, YELLOW);
                }
            }
            else
                cout<<"Mouse didn't clicked inside the start";
        }

    draw_polygon(points, YELLOW);
//            Scanline(points, GREEN, YELLOW);
    if(flag)
        BoundaryFill(PT(points[2].x, points[2].y-10), YELLOW, GREEN);



    while(true)
    {
        x = y = 0;
        if(GetAsyncKeyState(VK_UP))
        {
            y+=5;
            cout<<"UP"<<endl;
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            x+=5;
            cout<<"RIGHT"<<endl;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            y-=5;
            cout<<"DOWN"<<endl;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            x-=5;
            cout<<"LEFT"<<endl;
        }

        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if(mx != -1 && my != -1)
        {
//            pii pixel = shift_pixel(mx, my);
//            cout<<mx<<" mouse "<<my<<endl;
//            cout<<pixel.first<<" Pixel "<<pixel.second<<endl;
            int r = mx;
            int l = mx;
            while(r<(window_w))
            {
                if(getpixel(r, my)==YELLOW)
                    break;
                r++;
            }
            while(l>0)
            {
                if(getpixel(l, my)==YELLOW)
                    break;
                l--;
            }
            if(r!=(window_w) && l!=0)
            {
                cout<<"Mouse clicked inside the star!"<<endl;
                flag = !flag;
                if(flag)
                    BoundaryFill(PT(points[2].x, points[2].y-10), YELLOW, GREEN);
                else
                {
                    cleardevice();
                    //draw_axis();
                    draw_polygon(points, YELLOW);
                }
            }
            else
                cout<<"Mouse didn't clicked inside the start"<<endl;
        }

        if(x!=0 || y!=0)
        {
            if(points[0].x + x<=-400 || points[4].x + x >= 400 || points[2].y + y>=300 || points[8].y + y<=-300)
                    continue;
            for(int i = 0; i<points.size(); i++)
            {
                points[i].x = (int)(points[i].x + x)%(window_w/2);
                points[i].y = (int)(points[i].y + y)%(window_h/2);
            }
            cleardevice();
            //draw_axis();
            draw_polygon(points, YELLOW);
//            Scanline(points, GREEN, YELLOW);
            if(flag)
                BoundaryFill(PT(points[2].x, points[2].y-10), YELLOW, GREEN);
        }


        Sleep(10);
    }

    system("pause");

    return 0;
}

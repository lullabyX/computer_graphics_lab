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

void Scanline(vector<PT> points, int color)
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
            Bressenham(intersects[i], intersects[i+1], color);
        }
    }
}

int main()
{
    initwindow(window_w, window_h);
    int backgroundColor = getpixel(0,0);
    draw_axis();

    vector<PT> points;

    points.push_back(PT(-100, -100));
    points.push_back(PT(-50, -125));
    points.push_back(PT(50, -50));
    points.push_back(PT(100, -125));
    points.push_back(PT(200, -50));
    points.push_back(PT(200, 100));
    points.push_back(PT(0, 150));
    points.push_back(PT(-100, 50));
    points.push_back(PT(-200, 50));

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

    draw_polygon(points, YELLOW);
    Scanline(points, GREEN);


    system("pause");

    return 0;
}

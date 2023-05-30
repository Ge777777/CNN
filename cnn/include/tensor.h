#pragma once

#include<string.h>
#include<iostream>

struct size_s
{
    int x,y,z;
    size_s operator/(const int stride)
    {
        size_s now=(*this);
        now.x/=stride,now.y/=stride;
        return now;
    }

    size_s operator-(const size_s &F)
    {
        size_s now=(*this);
        now.x-=F.x,now.y-=F.y;
        return now;
    }

    size_s operator+(const int v)
    {
        size_s now=(*this);
        now.x+=v;now.y+=v;
        return now;
    }

    size_s operator-(const int v)
    {
        size_s now=(*this);
        now.x-=v;now.y-=v;
        return now;
    }
};
// int totnums=0;
template<typename D>
struct tensor
{
    D* data;

    size_s Lim;
    //实现拷贝构造函数
    tensor<D> clone()
    {
        tensor<D> now(this->Lim);
        int sz=this->Lim.x * this->Lim.y * this->Lim.z;
        memcpy(now.data,this->data,sz*sizeof(D));
        return now;
    }
    tensor(){Lim.x=0,Lim.y=0,Lim.z=0;data=nullptr;}
    tensor(int x,int y,int z)
    {
        Lim=(size_s){x,y,z};
        data=new D[x*y*z];memset(data,0,sizeof(data));
    }

    tensor(size_s F)
    {
        int x=F.x,y=F.y,z=F.z;
        data=new D[x*y*z];memset(data,0,sizeof(data));
        Lim=F;
    }

    int size(){return Lim.x*Lim.y*Lim.z;}

    tensor(const tensor& F)
    {
        int sz=F.Lim.x*F.Lim.y*F.Lim.z;
        data=new D[sz];
        memcpy(data,F.data,sz*sizeof(D));
        Lim.x = F.Lim.x,Lim.y = F.Lim.y,Lim.z = F.Lim.z;
    }

    tensor<D> &operator=(const tensor<D> &F) {
        if(this->data!=nullptr) delete[] this->data;
        int sz=F.Lim.x*F.Lim.y*F.Lim.z;
        data=new D[sz];
        memcpy(data,F.data,sz*sizeof(D));
        Lim.x = F.Lim.x,Lim.y = F.Lim.y,Lim.z = F.Lim.z;
        return *this;
    }


    tensor<D> operator+(const tensor<D> &F)
    {
        tensor<D> now(*this);
        int sz=F.Lim.x*F.Lim.y*F.Lim.z;
        for(int i=0;i<sz;i++) now.data[i] += F.data[i];
        return now;
    }

    tensor<D> operator-(const tensor<D> &F)
    {
        tensor<D> now(*this);
        int sz=F.Lim.x*F.Lim.y*F.Lim.z;
        for(int i=0;i<sz;i++) now.data[i] -= F.data[i];
        return now;
    }

    tensor<D> operator*(const tensor<D> &F)
    {
        int xx=Lim.x,yy=Lim.y,zz=Lim.z,mm=F.Lim.y;
        tensor<double> now(xx,mm,zz);
        for(int z=0;z<zz;z++)
        for(int i=0;i<xx;i++)
        for(int j=0;j<yy;j++)
        for(int k=0;k<mm;k++) now(i,k,z)+=this->data[id(i,j,z)]*F.data[F.id(j,k,z)];
        return now;
    }
    
    tensor<D> transpose()
    {
        int xx=Lim.x,yy=Lim.y,zz=Lim.z;
        tensor<D> now(yy,xx,zz);
        for(int z=0;z<zz;z++)
        for(int x=0;x<xx;x++)
        for(int y=0;y<yy;y++) now[now.id(y,x,z)]=this->data[this->id(x,y,z)];
        return now;
    }
    int id(int x,int y,int z) const{return z*(Lim.x*Lim.y)+y*(Lim.x)+x;}

    int id(int x,int y,int z){return z*(Lim.x*Lim.y)+y*(Lim.x)+x;}

    D& operator()(int x,int y,int z){return this->data[id(x,y,z)];}

    const D& operator() (int x, int y, int z) const { return this->data[id(x, y, z)]; }

    D& get(int x,int y,int z){return this->data[this->id(x,y,z)];}
    
    D& operator[](int x){return data[x];}
    
    ~tensor(){
        free(data);
        data = nullptr;
    }
};
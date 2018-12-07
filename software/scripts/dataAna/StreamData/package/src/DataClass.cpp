#include <iostream>
#include <vector>
#include "../include/DataClass.h"
#include "../include/comm.h"
#include <bitset>

DataClass::DataClass()
{
}

DataClass::DataClass(struct Frame *frame)
{
    uint16_t data_t;
    int m_d=0;
    for (int j=0;j<frame->payload_size;j++){ 
        data_t=frame->payload[j];

        if (data_t>0){
        m_d=j%4;
        switch(m_d){
            case 0:add_data(data_t,0);break;
            case 1:add_data(data_t,1);break;
            case 2:add_data(data_t,2);break;
            default: break;
            }
       }

   }
}
DataClass::~DataClass()
{
}

void DataClass::setFrame(struct Frame *frame)
{

    uint16_t data_t;
    int m_d=0;
    for (int j=0;j<frame->payload_size;j++){ 
        data_t=frame->payload[j];

        if (data_t>0){
        m_d=j%4;
        switch(m_d){
            case 0:add_data(data_t,0);break;
            case 1:add_data(data_t,1);break;
            case 2:add_data(data_t,2);break;
            default: break;
            }
       }
   }
}

void DataClass::Init()
{
    _Matrix0.clear();
    _Matrix1.clear();
    _Matrix2.clear();


}
void DataClass::add_data(uint16_t data_t,int matrix_t)
{
   
    int Row,Col,Muli_flag,DV_flag;
    std::vector<int> p;
    Row = data_t & 0x007f; 
    Col = data_t & 0x0f80; Col>>=7;
    Muli_flag = (data_t & 0x1000)>0;
    DV_flag=(data_t & 0x2000)>0;
   
    if (DV_flag>0){
        p.push_back(Row);
        p.push_back(Col);
        switch ( matrix_t){
            case 0: _Matrix0.push_back(p);break;
            case 1: _Matrix1.push_back(p);break;
            case 2: _Matrix2.push_back(p);break;
            default: break;
        }

    }
}

std::vector<std::vector <int> > DataClass::get_Hitmap(int matrix)
{
    if (matrix==0){
        return _Matrix0;
    }
    if (matrix==1){
        return _Matrix1;
    }
    if (matrix==2){
        return _Matrix2;
    }
    
}

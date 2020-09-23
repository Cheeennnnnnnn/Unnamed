#include "csvProcessor.h"

CsvProcessor::CsvProcessor() :
    deviceList(new List_ND()),
    dataList(new List_CD())
{

}

void CsvProcessor::processData(CsvData data)
{
    if((data.s_Device_IP[0] == 0 && data.s_Device_IP[1] == 0 && data.s_Device_IP[2] == 0 && data.s_Device_IP[3] == 0) ||
       (data.d_Device_IP[0] == 0 && data.d_Device_IP[1] == 0 && data.d_Device_IP[2] == 0 && data.d_Device_IP[3] == 0))
    {
        return;
    }
    else
    {
        Node_CD* dataNode = dataList ->indexOfNode(data);
        if(dataNode == nullptr)
        {
            dataList ->addNode(data);
        }
        else
        {
            dataNode ->value.times++;
        }
//        Node_ND* temp = 
    }
}

void CsvProcessor::clearData(int timeStamp)
{
    int i = 0;
    for(Node_CD* index = dataList ->head ->right; index != dataList ->tail; index = index ->right, ++i)
    {
        if(index ->value.timeStamp < timeStamp)
        {
            Node_ND* temp = deviceList ->indexOfNode(index ->value.s_Device_IP);
            --temp ->value.sendTimes;
            if(!temp ->value.sendTimes && temp ->value.receiveTimes)
            {

                /**/
                deviceList ->deleteNode(temp);
            }
            temp = deviceList ->indexOfNode(index ->value.d_Device_IP);
            --temp ->value.receiveTimes;
            if(!temp ->value.sendTimes && temp ->value.receiveTimes)
            {

                /**/
                deviceList ->deleteNode(temp);
            }

            /**/
            dataList ->deleteNode(index);
        }
        else
        {
            return;
        }
    }
}

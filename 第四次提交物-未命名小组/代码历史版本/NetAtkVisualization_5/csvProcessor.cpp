#include "csvProcessor.h"

CsvProcessor::CsvProcessor(int _warningThreshold) :
    deviceList(new List_ND()),
    attackedDeviceList(new List_ND()),
    dataList(new List_CD()),
    lineList(new List_L()),
    warningThreshold(_warningThreshold),
    hasher(new IPHasher())
{
    
}

PointerWithNo_ND* CsvProcessor::indexOfDevice(unsigned char *ip, List_ND* tarList)
{
    int i = 0;
    for(Node_ND* index = tarList ->head ->right; index != tarList ->tail; index = index ->right, ++i)
    {
        if(index ->value == ip)
        {
            return new PointerWithNo_ND(index, i);
        }
    }
    return nullptr;
}

PointerWithNo_L* CsvProcessor::indexOfLine(CsvData data)
{
    int i = 0;
    for(Node_L* index = lineList ->head ->right; index != lineList ->tail; index = index ->right, ++i)
    {
        if(data == index ->value)
        {
            return new PointerWithNo_L(index, i);
        }
    }
    return nullptr;
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
        dataList ->addNode(data);

        PointerWithNo_ND* deviceIndex = indexOfDevice(data.s_Device_IP, deviceList);
        if(deviceIndex == nullptr)
        {
            Tuple<int, int> coordinate = hasher ->hash(data.s_Device_IP);
            int longitude = coordinate.value1;
            int latitude = coordinate.value2;
            QString ip = IP_to_QString(data.s_Device_IP);

            /*
             * 通知前端建立一个经纬坐标分别为longitude、latitude，IP为ip的点
            */

            deviceList ->addNode(data.s_Device_IP);
            deviceList ->tail ->left ->value.sendTimes = 1;
        }
        else
        {
            int tempTimes = ++deviceIndex ->pointer ->value.sendTimes;
            if(tempTimes >= warningThreshold)
            {
                Node_ND* attackedDeviceIndex = attackedDeviceList ->indexOfNode(deviceIndex ->pointer ->value);
                if(attackedDeviceIndex == nullptr)
                {
                    attackedDeviceList ->addNode(deviceIndex ->pointer ->value);
                    emit signalSenter ->underAttack(deviceIndex ->pointer ->value.IP, true, tempTimes);
                }
                else if(tempTimes - attackedDeviceIndex ->value.sendTimes >= warningThreshold / 10)
                {
                    attackedDeviceIndex ->value.sendTimes = tempTimes;
                    emit signalSenter ->underAttack(deviceIndex ->pointer ->value.IP, true, tempTimes);
                }
            }
        }

        deviceIndex = indexOfDevice(data.d_Device_IP, deviceList);
        if(deviceIndex == nullptr)
        {
            Tuple<int, int> coordinate = hasher ->hash(data.d_Device_IP);
            int longitude = coordinate.value1;
            int latitude = coordinate.value2;
            QString ip = IP_to_QString(data.d_Device_IP);

            /*
             * 通知前端建立一个经纬坐标分别为longitude、latitude，IP为ip的点
            */

            deviceList ->addNode(data.d_Device_IP);
            deviceList ->tail ->left ->value.receiveTimes = 1;
        }
        else
        {
            int tempTimes = ++deviceIndex ->pointer ->value.receiveTimes;
            if(tempTimes >= warningThreshold)
            {
                Node_ND* attackedDeviceIndex = attackedDeviceList ->indexOfNode(deviceIndex ->pointer ->value);
                if(attackedDeviceIndex == nullptr)
                {
                    attackedDeviceList ->addNode(deviceIndex ->pointer ->value);
                    emit signalSenter ->underAttack(deviceIndex ->pointer ->value.IP, false, tempTimes);
                }
                else if(tempTimes - attackedDeviceIndex ->value.receiveTimes >= warningThreshold / 10)
                {
                    attackedDeviceIndex ->value.receiveTimes = tempTimes;
                    emit signalSenter ->underAttack(deviceIndex ->pointer ->value.IP, false, tempTimes);
                }
            }
        }

        PointerWithNo_L* lineIndex = indexOfLine(data);
        if(lineIndex == nullptr)
        {
            int s = indexOfDevice(data.s_Device_IP, deviceList) ->no;
            int d = indexOfDevice(data.d_Device_IP, deviceList) ->no;

            /*
             * 通知前端建立一条长度为1，起点序号为s，终点序号为d的线
            */

            lineList ->addNode(Line(data.s_Device_IP, data.d_Device_IP));
        }
        else
        {
            int lineNo = lineIndex ->no;
            int newWidth = ++lineIndex ->pointer ->value.times;

            /*
             * 通知前端将序号为lineNo的线的宽度改为newWidth
            */

        }

        delete deviceIndex;
        delete lineIndex;
    }
}

void CsvProcessor::clearData(int timeStamp)
{
    int i = 0;

//    Node_CD* lastIndex, *llIndex, *lllIndex, *llllIndex;

    for(Node_CD* index = dataList ->head ->right; index != dataList ->tail;/*llllIndex = lllIndex, lllIndex = llIndex, llIndex = lastIndex, lastIndex = index, */index = index ->right, ++i)
    {
        if(index ->value.timeStamp < timeStamp)
        {
            PointerWithNo_ND* deviceIndex = indexOfDevice(index ->value.s_Device_IP, deviceList);
            if(deviceIndex != nullptr)
            {
                int deviceNo = deviceIndex ->no;
                int newSendTimes = --deviceIndex ->pointer ->value.sendTimes;
                int receiveTimes = deviceIndex ->pointer ->value.receiveTimes;
                if(!newSendTimes && !receiveTimes)
                {
                    /*
                     * 通知前端将序号为deviceNo的结点删除
                    */

                    deviceList ->deleteNode(deviceIndex ->pointer);
                }
            }
            deviceIndex = indexOfDevice(index ->value.d_Device_IP, deviceList);
            if(deviceIndex != nullptr)
            {
                int deviceNo = deviceIndex ->no;
                int newReceiveTimes = --deviceIndex ->pointer ->value.receiveTimes;
                int sendTimes = deviceIndex ->pointer ->value.sendTimes;
                if(!sendTimes && !newReceiveTimes)
                {
                    /*
                     * 通知前端将序号为deviceNo的结点删除
                    */

                    deviceList ->deleteNode(deviceIndex ->pointer);
                }

            }
            deviceIndex = indexOfDevice(index ->value.s_Device_IP, attackedDeviceList);
            if(deviceIndex != nullptr)
            {
                int newSendTimes = --deviceIndex ->pointer ->value.sendTimes;
                int receiveTimes = deviceIndex ->pointer ->value.receiveTimes;
                if(newSendTimes < warningThreshold && receiveTimes < warningThreshold)
                {
                    attackedDeviceList ->deleteNode(deviceIndex ->pointer);
                }
            }
            deviceIndex = indexOfDevice(index ->value.d_Device_IP, attackedDeviceList);
            if(deviceIndex != nullptr)
            {
                int newReceiveTimes = --deviceIndex ->pointer ->value.receiveTimes;
                int sendTimes = deviceIndex ->pointer ->value.sendTimes;
                if(sendTimes < warningThreshold && newReceiveTimes < warningThreshold)
                {
                    attackedDeviceList ->deleteNode(deviceIndex ->pointer);
                }

            }

            PointerWithNo_L* lineIndex = indexOfLine(index ->value);
            if(lineIndex != nullptr)
            {
                int lineNo = lineIndex ->no;
                int newWidth = --lineIndex ->pointer ->value.times;
                if(!newWidth)
                {
                    /*
                     * 通知前端将序号为lineNo的线删除
                    */

                    lineList ->deleteNode(lineIndex ->pointer);
                }
                else
                {
                    /*
                     * 通知前端将序号为lineNo的线的宽度改为newWidth
                    */
                }
            }

            dataList ->deleteNode(index);
        }
        else
        {
            return;
        }
    }
}

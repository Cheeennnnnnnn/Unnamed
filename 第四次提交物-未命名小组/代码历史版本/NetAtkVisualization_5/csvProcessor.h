#ifndef CSVPROCESSOR_H
#define CSVPROCESSOR_H

#include "netDevice.h"
#include "csvData.h"
#include "pointerWithNo.h"
#include "ipHasher.h"
#include "signalSenter.h"

#define List_ND List<NetDevice>
#define List_CD List<CsvData>
#define List_L List<Line>
#define Node_ND Node<NetDevice>
#define Node_CD Node<CsvData>
#define Node_L Node<Line>
#define PointerWithNo_ND PointerWithNo<NetDevice>
#define PointerWithNo_L PointerWithNo<Line>

class CsvProcessor
{
public:
    List_ND* deviceList;
    List_ND* attackedDeviceList;
    List_CD* dataList;
    List_L* lineList;

    int warningThreshold;

    IPHasher* hasher;

public:
    CsvProcessor(int _warningThreshold = 10000);
    
    PointerWithNo_ND* indexOfDevice(unsigned char* ip, List_ND* tarList);
    PointerWithNo_L* indexOfLine(CsvData data);
    
    void processData(CsvData data);
    void clearData(int timeStamp);
};

#endif // CSVPROCESSOR_H

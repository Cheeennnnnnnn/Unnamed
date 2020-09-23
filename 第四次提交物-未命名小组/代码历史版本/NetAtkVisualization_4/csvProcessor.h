#ifndef CSVPROCESSOR_H
#define CSVPROCESSOR_H

#include "netDevice.h"
#include "csvData.h"

#define List_ND List<NetDevice>
#define List_CD List<CsvData>
#define Node_ND Node<NetDevice>
#define Node_CD Node<CsvData>

class CsvProcessor
{
public:
    List_ND* deviceList;
    List_CD* dataList;

public:
    CsvProcessor();

    void processData(CsvData data);
    void clearData(int timeStamp);
};

#endif // CSVPROCESSOR_H

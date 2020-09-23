#ifndef CSVPROCESSOR_H
#define CSVPROCESSOR_H

#include "netDevice.h"
#include "csvData.h"

#define List_nd List<NetDevice>
#define List_cd List<CsvData>
#define Node_nd Node<NetDevice>
#define Node_cd Node<CsvData>

class CsvProcessor
{
public:
    List_nd* deviceList;
    List_cd* dataList;

public:
    CsvProcessor();


};

#endif // CSVPROCESSOR_H

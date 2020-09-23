#include "csvProcessor.h"

CsvProcessor::CsvProcessor() :
    deviceList(new List<NetDevice>()),
    dataList(new List<CsvData>())
{

}

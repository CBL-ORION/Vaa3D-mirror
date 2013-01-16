#ifndef VOLUMEPATTERNINDEX_H
#define VOLUMEPATTERNINDEX_H

#include <QString>
#include <QtCore>
#include <QDir>
#include "../../v3d/v3d_core.h"

using namespace std;

class VolumePatternIndex
{
public:

    static const int MODE_UNDEFINED;
    static const int MODE_INDEX;
    static const int MODE_SEARCH;

    VolumePatternIndex();

    ~VolumePatternIndex();

    static string getCommandLineDescription() {
        return "volume-pattern-index";
    }

    static string getUsage() {
        string usage;
        usage.append("  Volume Pattern Index Tool                                                                             \n");
        usage.append("                                                                                                        \n");
        usage.append("    Tool for indexing and searching volumes for similar patterns                                        \n");
        usage.append("                                                                                                        \n");
        usage.append("     -mode [index|search]                                                                               \n");
        usage.append("     [ -subVolume \"x0 x1 y0 y1 z0 z1\" : default is full size ]                                        \n");
        usage.append("                                                                                                        \n");
        usage.append("    For mode index:                                                                                     \n");
        usage.append("                                                                                                        \n");
        usage.append("     -inputList <list of stacks to index>                                                               \n");
        usage.append("     -outputIndex <index file>                                                                          \n");
        usage.append("     [ -unitSize <voxels per cube side> : default=10 ]                                                  \n");
        usage.append("     [ -threshold \"a b c\" : default a=6, b=20, c=50 , creates 4 scoring bins ]                        \n");
        usage.append("                                                                                                        \n");
        usage.append("    For mode search:                                                                                    \n");
        usage.append("                                                                                                        \n");
        usage.append("     -query <image volume to use as query>                                                              \n");
        usage.append("     [ -maxHits <maximum number of hits> : default=100 ]                                                \n");
        usage.append("     [ -fast : search only using index, faster but less accurate ]                                      \n");
        usage.append("     [ -matrix \"t0s0 t0s1 t0s2 t0s3 ... t3s0 t3s1 t3s2 t3s3\" : the 16 values for score matrix ]       \n");
        usage.append("                                                                                                        \n");
        return usage;
    }

    bool execute();
    int processArgs(vector<char*> *argList);

private:

    int mode;
    int x0,x1,y0,y1,z0,z1;

    QString modeString;

    QString inputFileList;
    QString outputIndexFile;
    int unitSize;
    int* threshold;

    QString queryImageFile;
    int maxHits;
    bool fastSearch;
    float* matrix;

    bool createSubVolume();
    bool createIndex();
    bool doSearch();

};

#endif // VOLUMEPATTERNINDEX_H

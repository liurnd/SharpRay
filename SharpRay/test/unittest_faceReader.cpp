#include <sstream>
#include <assert.h>
struct _ObjMeshFaceIndex{
    int pos_index[3];
    int tex_index[3];
    int nor_index[3];
};
void readFace(std::stringstream& ss, _ObjMeshFaceIndex& face);

#define VASSERT(result,a1,a2,a3,b1,b2,b3,c1,c2,c3) do{ \
    assert(result.pos_index[0]==a1);\
    assert(result.pos_index[1]==b1);\
    assert(result.pos_index[2]==c1);\
    assert(result.tex_index[0]==a2);\
    assert(result.tex_index[1]==b2);\
    assert(result.tex_index[2]==c2);\
    assert(result.nor_index[0]==a3);\
    assert(result.nor_index[1]==b3);\
    assert(result.nor_index[2]==c3);\
    } while(0)

#define readerTest(s, a1,a2,a3,b1,b2,b3,c1,c2,c3) do{\
    _ObjMeshFaceIndex result;\
    std::stringstream ss(s);\
    readFace(ss,result);\
    VASSERT(result, 119,0,233,158,0,244,157,0,235);\
    }while(0)

int main()
{
    readerTest("119//233 158//244 157//235", 119,0,233,158,0,244,157,0,235);
    readerTest("119/1/233 158/2/244 157/3/235", 119,1,233,158,2,244,157,3,235);
    readerTest("119/1 158/2 157/3", 119,1,0,158,2,0,157,3,0);
    readerTest("119 158 157", 119,0,0,158,0,0,157,0,0);
    return 0;
}

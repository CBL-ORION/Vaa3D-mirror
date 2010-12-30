// This file has been generated by Py++.

#include "boost/python.hpp"
#include "wrappable_v3d.h"
#include "Image4DSimple.pypp.hpp"

namespace bp = boost::python;

struct Image4DSimple_wrapper : Image4DSimple, bp::wrapper< Image4DSimple > {

    Image4DSimple_wrapper(Image4DSimple const & arg )
    : Image4DSimple( arg )
      , bp::wrapper< Image4DSimple >(){
        // copy constructor
        
    }

    Image4DSimple_wrapper( )
    : Image4DSimple( )
      , bp::wrapper< Image4DSimple >(){
        // null constructor
    
    }

    virtual void cleanExistData(  ) {
        if( bp::override func_cleanExistData = this->get_override( "cleanExistData" ) )
            func_cleanExistData(  );
        else{
            this->Image4DSimple::cleanExistData(  );
        }
    }
    
    void default_cleanExistData(  ) {
        Image4DSimple::cleanExistData( );
    }

    virtual bool valid(  ) {
        if( bp::override func_valid = this->get_override( "valid" ) )
            return func_valid(  );
        else{
            return this->Image4DSimple::valid(  );
        }
    }
    
    bool default_valid(  ) {
        return Image4DSimple::valid( );
    }

};

void register_Image4DSimple_class(){

    bp::class_< Image4DSimple_wrapper >( "Image4DSimple", "\n basic_4dimage.h\n\n This function is a basic function interface of the V3D project.\n\n Copyright: Hanchuan Peng (Howard Hughes Medical Institute, Janelia Farm Research Campus).\n The License Information and User Agreement should be seen at http://penglab.janelia.org/proj/v3d .\n\n Last edit: 2009-Aug-21\n Last edit: 2010-May-19: replace long with V3DLONG\n Last edit: 2010-May-30: add the value_at() function for Image4DProxy class\n Last edit: 2010-Jun-26: add three new members rez_x, rez_y, and rez_z which indicate the pixel sizes and thus the anisotropy of the image\n\n Last edit: 2010-Aug-1: add a function to determine if the data buffers of two images are exactly the same (but not their contents!)\n Last edit: 2010-Aug-3: add the put_at() function for Image4DProxy class\n Last edit: 2010-Aug-10: virtual destructor for other virtual functions in Image4DSimple\n Last edit: 2010-Aug-31: PHC. move private members to protected to fix the hackers bug!.\n Last edit: 2010-Oct-06. PHC. add the original_x,y,z fields\n Last edit: 2010-Oct-7. PHC. add a customary void pointer for a unknown struct for parameters passing of plugins\n Last edit: 2010-Dec-18. PHC. add a valid valid_zslicenum to indicate the reading status of the data\n", bp::init< >("\n basic_4dimage.h\n\n This function is a basic function interface of the V3D project.\n\n Copyright: Hanchuan Peng (Howard Hughes Medical Institute, Janelia Farm Research Campus).\n The License Information and User Agreement should be seen at http://penglab.janelia.org/proj/v3d .\n\n Last edit: 2009-Aug-21\n Last edit: 2010-May-19: replace long with V3DLONG\n Last edit: 2010-May-30: add the value_at() function for Image4DProxy class\n Last edit: 2010-Jun-26: add three new members rez_x, rez_y, and rez_z which indicate the pixel sizes and thus the anisotropy of the image\n\n Last edit: 2010-Aug-1: add a function to determine if the data buffers of two images are exactly the same (but not their contents!)\n Last edit: 2010-Aug-3: add the put_at() function for Image4DProxy class\n Last edit: 2010-Aug-10: virtual destructor for other virtual functions in Image4DSimple\n Last edit: 2010-Aug-31: PHC. move private members to protected to fix the hackers bug!.\n Last edit: 2010-Oct-06. PHC. add the original_x,y,z fields\n Last edit: 2010-Oct-7. PHC. add a customary void pointer for a unknown struct for parameters passing of plugins\n Last edit: 2010-Dec-18. PHC. add a valid valid_zslicenum to indicate the reading status of the data\n") )    
        .def( 
            "cleanExistData"
            , (void ( ::Image4DSimple::* )(  ) )(&::Image4DSimple::cleanExistData)
            , (void ( Image4DSimple_wrapper::* )(  ) )(&Image4DSimple_wrapper::default_cleanExistData) )    
        .def( 
            "deleteRawDataAndSetPointerToNull"
            , (void ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::deleteRawDataAndSetPointerToNull ) )    
        .def( 
            "getCDim"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getCDim ) )    
        .def( 
            "getCustomStructPointer"
            , (void * ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getCustomStructPointer )
            , bp::return_value_policy< bp::return_opaque_pointer >() )    
        .def( 
            "getDatatype"
            , (::ImagePixelType ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getDatatype ) )    
        .def( 
            "getError"
            , (int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getError ) )    
        .def( 
            "getFileName"
            , (char const * ( ::Image4DSimple::* )(  ) const)( &::Image4DSimple::getFileName ) )    
        .def( 
            "getOriginX"
            , (double ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getOriginX ) )    
        .def( 
            "getOriginY"
            , (double ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getOriginY ) )    
        .def( 
            "getOriginZ"
            , (double ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getOriginZ ) )    
        .def( 
            "getPreValidZSliceNum"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getPreValidZSliceNum ) )    
        .def( 
            "getRezX"
            , (double ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getRezX ) )    
        .def( 
            "getRezY"
            , (double ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getRezY ) )    
        .def( 
            "getRezZ"
            , (double ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getRezZ ) )    
        .def( 
            "getTDim"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getTDim ) )    
        .def( 
            "getTimePackType"
            , (::TimePackType ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getTimePackType ) )    
        .def( 
            "getTotalBytes"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getTotalBytes ) )    
        .def( 
            "getTotalUnitNumber"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getTotalUnitNumber ) )    
        .def( 
            "getTotalUnitNumberPerChannel"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getTotalUnitNumberPerChannel ) )    
        .def( 
            "getTotalUnitNumberPerPlane"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getTotalUnitNumberPerPlane ) )    
        .def( 
            "getUnitBytes"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getUnitBytes ) )    
        .def( 
            "getValidZSliceNum"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getValidZSliceNum ) )    
        .def( 
            "getXDim"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getXDim ) )    
        .def( 
            "getYDim"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getYDim ) )    
        .def( 
            "getZDim"
            , (long int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::getZDim ) )    
        .def( 
            "isSameDataBuffer"
            , (bool ( ::Image4DSimple::* )( ::Image4DSimple * ) )( &::Image4DSimple::isSameDataBuffer )
            , ( bp::arg("p") ) )    
        .def( 
            "isSuccess"
            , (int ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::isSuccess ) )    
        .def( 
            "isValidCustomStructPointer"
            , (bool ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::isValidCustomStructPointer ) )    
        .def( 
            "setCDim"
            , (void ( ::Image4DSimple::* )( long int ) )( &::Image4DSimple::setCDim )
            , ( bp::arg("v") ) )    
        .def( 
            "setCustomStructPointer"
            , (void ( ::Image4DSimple::* )( void * ) )( &::Image4DSimple::setCustomStructPointer )
            , ( bp::arg("a") ) )    
        .def( 
            "setData"
            , (bool ( ::Image4DSimple::* )( unsigned char *,::Image4DSimple * ) )( &::Image4DSimple::setData )
            , ( bp::arg("p"), bp::arg("image") ) )    
        .def( 
            "setData"
            , (bool ( ::Image4DSimple::* )( unsigned char *,long int,long int,long int,long int,::ImagePixelType ) )( &::Image4DSimple::setData )
            , ( bp::arg("p"), bp::arg("s0"), bp::arg("s1"), bp::arg("s2"), bp::arg("s3"), bp::arg("dt") ) )    
        .def( 
            "setDatatype"
            , (void ( ::Image4DSimple::* )( ::ImagePixelType ) )( &::Image4DSimple::setDatatype )
            , ( bp::arg("v") ) )    
        .def( 
            "setFileName"
            , (bool ( ::Image4DSimple::* )( char const * ) )( &::Image4DSimple::setFileName )
            , ( bp::arg("myfile") ) )    
        .def( 
            "setNewRawDataPointer"
            , (bool ( ::Image4DSimple::* )( unsigned char * ) )( &::Image4DSimple::setNewRawDataPointer )
            , ( bp::arg("p") ) )    
        .def( 
            "setOriginX"
            , (void ( ::Image4DSimple::* )( double ) )( &::Image4DSimple::setOriginX )
            , ( bp::arg("a") ) )    
        .def( 
            "setOriginY"
            , (void ( ::Image4DSimple::* )( double ) )( &::Image4DSimple::setOriginY )
            , ( bp::arg("a") ) )    
        .def( 
            "setOriginZ"
            , (void ( ::Image4DSimple::* )( double ) )( &::Image4DSimple::setOriginZ )
            , ( bp::arg("a") ) )    
        .def( 
            "setPreValidZSliceNum"
            , (bool ( ::Image4DSimple::* )( long int ) )( &::Image4DSimple::setPreValidZSliceNum )
            , ( bp::arg("v") ) )    
        .def( 
            "setRawDataPointer"
            , (void ( ::Image4DSimple::* )( unsigned char * ) )( &::Image4DSimple::setRawDataPointer )
            , ( bp::arg("p") ) )    
        .def( 
            "setRawDataPointerToNull"
            , (void ( ::Image4DSimple::* )(  ) )( &::Image4DSimple::setRawDataPointerToNull ) )    
        .def( 
            "setRezX"
            , (bool ( ::Image4DSimple::* )( double ) )( &::Image4DSimple::setRezX )
            , ( bp::arg("a") ) )    
        .def( 
            "setRezY"
            , (bool ( ::Image4DSimple::* )( double ) )( &::Image4DSimple::setRezY )
            , ( bp::arg("a") ) )    
        .def( 
            "setRezZ"
            , (bool ( ::Image4DSimple::* )( double ) )( &::Image4DSimple::setRezZ )
            , ( bp::arg("a") ) )    
        .def( 
            "setTDim"
            , (void ( ::Image4DSimple::* )( long int ) )( &::Image4DSimple::setTDim )
            , ( bp::arg("v") ) )    
        .def( 
            "setTimePackType"
            , (void ( ::Image4DSimple::* )( ::TimePackType ) )( &::Image4DSimple::setTimePackType )
            , ( bp::arg("v") ) )    
        .def( 
            "setValidZSliceNum"
            , (bool ( ::Image4DSimple::* )( long int ) )( &::Image4DSimple::setValidZSliceNum )
            , ( bp::arg("v") ) )    
        .def( 
            "setXDim"
            , (void ( ::Image4DSimple::* )( long int ) )( &::Image4DSimple::setXDim )
            , ( bp::arg("v") ) )    
        .def( 
            "setYDim"
            , (void ( ::Image4DSimple::* )( long int ) )( &::Image4DSimple::setYDim )
            , ( bp::arg("v") ) )    
        .def( 
            "setZDim"
            , (void ( ::Image4DSimple::* )( long int ) )( &::Image4DSimple::setZDim )
            , ( bp::arg("v") ) )    
        .def( 
            "valid"
            , (bool ( ::Image4DSimple::* )(  ) )(&::Image4DSimple::valid)
            , (bool ( Image4DSimple_wrapper::* )(  ) )(&Image4DSimple_wrapper::default_valid) );

}

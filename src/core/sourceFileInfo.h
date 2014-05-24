#ifndef _core_sourceFileInfo_H_
#define _core_sourceFileInfo_H_

#include "boost/filesystem.hpp"
#include "core/foundation.h"
#include "core/object.h"
#include "core/pathname.fwd.h"
#include "core/fileSystem.fwd.h"
#include "core/sourceFileInfo.fwd.h"
    
namespace core
{
    class SourceFileInfo_O : public T_O
    {
	LISP_BASE1(T_O);
	LISP_CLASS(core,CorePkg,SourceFileInfo_O,"SourceFileInfo");
	DECLARE_INIT();
    public:
	static SourceFileInfo_sp getOrCreate(const string& fileNamePath);
	static SourceFileInfo_sp getOrCreate(Pathname_sp path);

    public: // ctor/dtor for classes with shared virtual base
	explicit SourceFileInfo_O();
	virtual ~SourceFileInfo_O() {};
	void initialize();
    private: // instance variables here
	Pathname_sp	_pathname;
	/*! Allocated buffer that stores the file name until the program exits */
	char* 	_PermanentPathName;
	char*	_PermanentFileName;
    public: // Functions here
	string fileName() const;
	string parentPathName() const;
	string namestring() const;
	Pathname_sp pathname() const { return this->_pathname;};
	const char* permanentPathName();
	const char* permanentFileName();

	string __repr__() const;
    }; // SourceFileInfo class





    FORWARD(SourcePosInfo);
    class SourcePosInfo_O : public T_O
    {
        friend class SourceManager_O;
	LISP_BASE1(T_O);
	LISP_CLASS(core,CorePkg,SourcePosInfo_O,"SourcePosInfo");
    public:
    public: // ctor/dtor for classes with shared virtual base
	explicit SourcePosInfo_O() : _FileId(UNDEF_UINT), _LineNumber(UNDEF_UINT),_Column(UNDEF_UINT), _FilePos(UNDEF_UINT) {};
    public: // instance variables here
	SourcePosInfo_O(uint spf, uint spln, uint spc, uint filePos, Function_sp expander=_Nil<Function_O>())
	    : _FileId(spf), _LineNumber(spln), _Column(spc), _FilePos(filePos), _Expander(expander) {}

    public:

        static SourcePosInfo_sp create(uint spf, uint spln=UNDEF_UINT, uint spc=UNDEF_UINT, uint filePos=UNDEF_UINT, Function_sp fn=_Nil<Function_O>() )
        {
            GC_ALLOCATE_VARIADIC(SourcePosInfo_O,me,spf,spln,spc,filePos,fn);
            return me;
        }

    protected:
	uint	_FileId;
	uint	_LineNumber;
	uint	_Column;
	uint	_FilePos;
	Function_sp 	_Expander;
    };



    class SourceManager_O : public T_O
    {
	LISP_BASE1(T_O);
	LISP_CLASS(core,CorePkg,SourceManager_O,"SourceManager");
	DECLARE_INIT();
        void initialize();
    public: // ctor/dtor for classes with shared virtual base
	explicit SourceManager_O() {};
	virtual ~SourceManager_O() {};
    public: // instance variables here
        // TODO!!!!! Use a WeakKeyHashTable_sp here
        // Must be implemented first!!!!
        HashTableEq_sp                         _SourcePosInfo;
//	map<T_wp,SourcePosInfo>			_SourcePosInfo;
	/*! All SourceFileInfo_sp source files are stored here indexed by integer FileId */
        gctools::Vec0<SourceFileInfo_sp>		_Files;
    public: // Functions here
#if 0
	SourceLocation createForSourceFile(const string& fileName);
	SourceFileInfo_sp getSourceFile(SourceLocation);

	SourceLocation createForSourceLocation(SourceLocation fileInfo, uint lineNumber, uint column );
	SourceLocation createForSourceLocation(SourceFileInfo_sp file, uint lineNumber, uint column );

	T_mv getSourceInfo(SourceLocation sourceLoc);
#endif

	/*! Register the object with the source manager */
	void registerSourceInfo(T_sp obj, SourceFileInfo_sp sourceFile, uint lineno, uint column, uint sourcePos, Function_sp expander=_Nil<Function_O>() );

	void registerSourceInfoFromStream(T_sp obj, Stream_sp stream);

	bool searchForSourceInfoAndDuplicateIt(T_sp orig, T_sp newObj);

	/*! Duplicate the source code information associated with orig_obj for new_obj */
	void duplicateSourceInfo(T_sp orig_obj, T_sp new_obj);

	/*! Duplicate the source code information for a macro expansion associated 
	  from orig_obj for new_obj */
	void duplicateSourceInfoForMacroExpansion(T_sp orig_obj, Function_sp expansionFunction, T_sp new_obj);

	/*! Return (values SourceFileInfo_sp lineno column sourcePos macroObject? ) for obj
          or (values) if nothing is found */
	SourceFileInfo_mv lookupSourceInfo(T_sp obj);

    }; // SourceManager class


    SourceFileInfo_mv af_lookupSourceFileInfo(T_sp obj);


    SourceFileInfo_sp af_sourceFileInfo(T_sp obj);


}; // core namespace
TRANSLATE(core::SourceFileInfo_O);
TRANSLATE(core::SourcePosInfo_O);
TRANSLATE(core::SourceManager_O);
    
extern "C" {
    void dumpSourceInfo(core::T_sp exp);
};



    

#endif /* _core_sourceFileInfo_H_ */

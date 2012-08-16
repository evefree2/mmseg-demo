#ifndef MMSEG_INTERFACE_H_
#define MMSEG_INTERFACE_H_
/*
 * Version 0.1
 * using libmmseg 
 * Created By edgar
 * arong2012a@gmail.com
 * */
#include "define.h"
//include libmmseg include file.
#include "SegmenterManager.h"
#include "Segmenter.h"
#include "csr_utils.h"
//include libmmseg end.
//
using namespace css;

class cmmseg{

public:
	cmmseg();
	~cmmseg();
public:
	int init_mmseg_libpath(const char* path);
	int loadsegmenter();
	void getallseg(const char* buffer,int length);

private:
	SegmenterManager* mgr;
	Segmenter* seg;

private:
	bool nRetMMSeg;
	const static u1 SEG_METHOD_NGRAM = 0x1;
};


#endif //end define mmseg_interface_h_

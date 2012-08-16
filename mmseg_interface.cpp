/*
 * Created By edgar
 * arong2012a@gmail.com
 * using libmmseg for chinese
 * */
#include "mmseg_interface.h"

cmmseg::cmmseg(){
	//init mgr
	mgr = new SegmenterManager();
	nRetMMSeg=false;
}
cmmseg::~cmmseg(){
	if(mgr){
		delete mgr;
	}
	nRetMMSeg=false;
}
int cmmseg::init_mmseg_libpath(const char* path){
	int nRet = 0;
	nRet = mgr->init(path);	
	if(0 == nRet){
		//set init mmseg path flag.
		nRetMMSeg=true;
	}
	return nRet;//only 0 is right. !=0 is error.
}
int cmmseg::loadsegmenter(){
	if(!nRetMMSeg){
		return -1;
	}
	//will delete when delete mgr
	seg=mgr->getSegmenter();
	return 0;
}
void cmmseg::getallseg(const char* buffer,int length){

	//begin seg
	seg->setBuffer((u1*)buffer,length);
	u2 len = 0, symlen = 0;
	u2 kwlen = 0, kwsymlen = 0;
	//check 1st token.
	char txtHead[3] = {239,187,191};
	char* tok = (char*)seg->peekToken(len, symlen);
	seg->popToken(len);
	if(seg->isSentenceEnd()){
		do {
			char* kwtok = (char*)seg->peekToken(kwlen , kwsymlen,1);
			if(kwsymlen)
				printf("[kw]%*.*s/x ",kwsymlen,kwsymlen,kwtok);
		}while(kwsymlen);
	}
	if(len == 3 && memcmp(tok,txtHead,sizeof(char)*3) == 0){
		//check is 0xFEFF
		//do nothing
	}else{
		printf("%*.*s/x ",symlen,symlen,tok);
	}
	while(1){
		len = 0;
		char* tok = (char*)seg->peekToken(len,symlen);
		if(!tok || !*tok || !len)
			break;
		seg->popToken(len);
		if(seg->isSentenceEnd()){
			do {
				char* kwtok = (char*)seg->peekToken(kwlen , kwsymlen,1);
				if(kwsymlen)
					printf("[kw]%*.*s/x ",kwsymlen,kwsymlen,kwtok);
			}while(kwsymlen);
		}

		if(*tok == '\r')
			continue;
		if(*tok == '\n'){
			printf("\n");
			continue;
		}

		//printf("[%d]%*.*s/x ",len,len,len,tok);
		printf("%*.*s/x ",symlen,symlen,tok);
		//check thesaurus
		{
			const char* thesaurus_ptr = seg->thesaurus(tok, symlen);
			while(thesaurus_ptr && *thesaurus_ptr) {
				len = strlen(thesaurus_ptr);
				printf("%*.*s/s ",len,len,thesaurus_ptr);
				thesaurus_ptr += len + 1; //move next
			}
		}
		//printf("%s",tok);
	}
	return ;
}

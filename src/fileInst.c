/**
 *    Copyright 2017 Luis Hsu
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "fileInst.h"

FileInst *fileInstNew(char *fname){
	FileInst *newFileInst = (FileInst *)malloc(sizeof(FileInst));
	newFileInst->fptr = fopen(fname, "rb");
	if(errno){
		perror(fname);
		return NULL;
	}
	newFileInst->fname = (char *)calloc(strlen(fname), sizeof(char));
	strcpy(newFileInst->fname, fname);
	newFileInst->curline = 1;
	return newFileInst;
}
void fileInstFree(FileInst **finst){
	fclose((*finst)->fptr);
	free((*finst)->fname);
	free(*finst);
	*finst = NULL;
}
int nextc(FileInst *fileInst){
	char thisChar = fgetc(fileInst->fptr);
	while(thisChar != EOF && thisChar == '\\'){
		char next = fgetc(fileInst->fptr);
		if(next == '\n'){
			++fileInst->curline;
			thisChar = fgetc(fileInst->fptr);
		}else{
			ungetc(next, fileInst->fptr);
			thisChar = '\\';
			break;
		}
	}
	return thisChar;
}

char *getShortName(FileInst *inst){
	return strrchr(inst->fname, DELIM_CHAR) + 1;
}
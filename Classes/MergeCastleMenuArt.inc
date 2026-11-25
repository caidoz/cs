// Closed-exterior upgrade illustrations; interiors are deliberately deferred.
static void RebuildPreview(int c,int x,int top,int width,int height,bool moving=false){
 MergeRouletteOriginalPreview(c,x,top,width,height,moving);
}
static void PartIcon(int c,int part,int lv,int x,int top,int size){
 (void)lv;
 if(part==0||part==1){MergeRouletteOriginalPreview(c,x,top,size,size);return;}
 MergeRouletteUiGlyph(part==3?0:part==4?8:9,x,top,size,size);
}

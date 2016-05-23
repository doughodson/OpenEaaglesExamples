
#include "fx.h"
#include "fx3d.h"

#include <GL/glu.h>

#include "GLSettingsDialog.h"

#define PRINT_YESNO(x) ( x ? "yes" : "no" )

// Implementation
FXDEFMAP(GLSettingsDialog) GLSettingsDialogMap[]={
  FXMAPFUNC(SEL_COMMAND,GLSettingsDialog::ID_SAVE,GLSettingsDialog::onCmdSave)
  };


FXIMPLEMENT(GLSettingsDialog,FXDialogBox,GLSettingsDialogMap,ARRAYNUMBER(GLSettingsDialogMap))

// Default constructor
GLSettingsDialog::GLSettingsDialog():canvas(nullptr),thickfont(nullptr),extensionlist(nullptr)
{}


// Construct with GL canvas (free floating version)
GLSettingsDialog::GLSettingsDialog(FXApp *a,FXGLCanvas *ca):FXDialogBox(a,FXString::null,DECOR_STRETCHABLE|DECOR_TITLE|DECOR_BORDER,0,0,0,0,0,0,0,0,0,0),canvas(ca),thickfont(NULL),extensionlist(NULL)
{
   setup();
}

// Construct with GL canvas (modal version)
GLSettingsDialog::GLSettingsDialog(FXWindow *o,FXGLCanvas *ca):FXDialogBox(o,FXString::null,DECOR_STRETCHABLE|DECOR_TITLE|DECOR_BORDER,0,0,0,0,0,0,0,0,0,0),canvas(ca),thickfont(NULL),extensionlist(NULL)
{
   setup();
}

void GLSettingsDialog::setup()
{
   FXVerticalFrame   *vframe;
   FXHorizontalFrame *hframe;
   FXMatrix          *matrix;
   FXLabel           *label;

   FXFontDesc fontdescription=getApp()->getNormalFont()->getFontDesc();
   fontdescription.weight=FXFont::DemiBold;
   thickfont=new FXFont(getApp(),fontdescription);
   thickfont->create();

   FXGLVisual *glvisual=(FXGLVisual*)canvas->getVisual();
   canvas->makeCurrent();

   GLint	intval;
   GLint	intvals[2];
   char *token, *text, *tmp;

   setTitle(tr("OpenGL Information"));

   hframe=new FXHorizontalFrame(this,LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
   new FXButton(hframe,tr("Close"),nullptr,this,ID_ACCEPT,FRAME_RAISED|FRAME_THICK|LAYOUT_RIGHT|BUTTON_DEFAULT|BUTTON_INITIAL,0,0,0,0,20,20,2,2);
   new FXButton(hframe,tr("Save"),nullptr,this,ID_SAVE,FRAME_RAISED|FRAME_THICK|LAYOUT_RIGHT,0,0,0,0,20,20,2,2);

   FXTabBook *tabbook=new FXTabBook(this,nullptr,0,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0);


   new FXTabItem(tabbook,tr(" Display Mode "));
   matrix=new FXMatrix(tabbook,2,MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED|FRAME_THICK);

   label=new FXLabel(matrix,tr("Hardware-accelerated:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,tr(PRINT_YESNO(glvisual->isAccelerated())),nullptr,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Double Buffering:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,tr(PRINT_YESNO(glvisual->isDoubleBuffer())),nullptr,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Stereo View:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,tr(PRINT_YESNO(glvisual->isStereo())),nullptr,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Buffer-swap by copy:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,tr(PRINT_YESNO(glvisual->isBufferSwapCopy())),nullptr,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Color Depth:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%d",glvisual->getActualRedSize()+glvisual->getActualGreenSize()+glvisual->getActualBlueSize()+glvisual->getActualAlphaSize()),NULL,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Depth Buffer Size:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%d",glvisual->getActualDepthSize()),nullptr,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Stencil Buffer Size:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%d",glvisual->getActualStencilSize()),nullptr,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("RGBA:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%d-%d-%d-%d",glvisual->getActualRedSize(),glvisual->getActualGreenSize(),glvisual->getActualBlueSize(),glvisual->getActualAlphaSize()),NULL,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Accum RGBA:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%d-%d-%d-%d",glvisual->getActualAccumRedSize(),glvisual->getActualAccumGreenSize(),glvisual->getActualAccumBlueSize(),glvisual->getActualAccumAlphaSize()),NULL,LABEL_NORMAL);

   label=new FXLabel(matrix,tr("Multi Sample:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%dx",glvisual->getActualMultiSamples()),nullptr,LABEL_NORMAL);

   new FXTabItem(tabbook,tr(" Limits "));
   matrix=new FXMatrix(tabbook, 2, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED|FRAME_THICK);

   glGetIntegerv(GL_MAX_VIEWPORT_DIMS, intvals);
   label=new FXLabel(matrix,tr("Viewport Size:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d x %d", intvals[0], intvals[1]));

   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &intval);
   label=new FXLabel(matrix,tr("Texture Size:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d", intval));

#if defined(GL_MAX_TEXTURE_UNITS)
   glGetIntegerv(GL_MAX_TEXTURE_UNITS, &intval);
   label=new FXLabel(matrix,tr("Texture Units:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d", intval));
#endif

   glGetIntegerv(GL_MAX_LIGHTS, &intval);
   label=new FXLabel(matrix,tr("Lights:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d", intval));

   glGetIntegerv(GL_MAX_CLIP_PLANES, &intval);
   label=new FXLabel(matrix,tr("Clipping Planes:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d", intval));

   glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &intval);
   label=new FXLabel(matrix,tr("Modelview Stack:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d", intval));

   glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &intval);
   label=new FXLabel(matrix,tr("Projection Stack:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d", intval));

   glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &intval);
   label=new FXLabel(matrix,tr("Attribute Stack:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix, FXString::value("%d", intval));

   label=new FXLabel(matrix,tr("Vertex Attributes:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
#if defined(GL_MAX_VERTEX_ATTRIBS)
   glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &intval);
   new FXLabel(matrix, FXString::value("%d", intval));
#else
   new FXLabel(matrix,"-");
#endif

   label=new FXLabel(matrix,tr("Vertex Uniform Components:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
#if defined(GL_MAX_VERTEX_UNIFORM_COMPONENTS)
   glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &intval);
   new FXLabel(matrix, FXString::value("%d", intval));
#else
   new FXLabel(matrix,"-");
#endif

   label = new FXLabel(matrix,tr("Fragment Uniform Components:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
#if defined(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS)
   glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &intval);
   new FXLabel(matrix, FXString::value("%d", intval));
#else
   new FXLabel(matrix,"-");
#endif

   new FXTabItem(tabbook,tr(" Extensions "));
   vframe=new FXVerticalFrame(tabbook,LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED|FRAME_THICK);

   vframe=new FXVerticalFrame(vframe,LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN|FRAME_THICK,0,0,0,0,0,0,0,0);
   extensionlist=new FXList(vframe,nullptr,0,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y|HSCROLLING_OFF);

   // Get OpenGL extensions
   tmp=(char*)glGetString(GL_EXTENSIONS);
   if (tmp) {
      text=strdup(tmp);
      token=strtok(text," ");
      while(token) {
         extensionlist->appendItem(token);
         token=strtok(nullptr," ");
      }
      free(text);
   }

   extensionlist->setSortFunc(FXList::ascending);
   extensionlist->sortItems();

   // Get GLU extensions
#ifdef GLU_VERSION_1_1
   tmp=(char*)gluGetString(GLU_EXTENSIONS);
   if (tmp) {
      text=strdup(tmp);
      token=strtok(text," ");
      while (token!=nullptr) {
         extensionlist->appendItem(token);
         token=strtok(nullptr," ");
      }
      free(text);
   }
#endif

   new FXTabItem(tabbook,tr(" Driver "));
   matrix=new FXMatrix(tabbook, 2, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_RAISED|FRAME_THICK);

   label = new FXLabel(matrix,tr("Vendor:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%s",glGetString(GL_VENDOR)),nullptr,LABEL_NORMAL);

   label = new FXLabel(matrix,tr("Renderer:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%s",glGetString(GL_RENDERER)),nullptr,LABEL_NORMAL);

   label = new FXLabel(matrix,tr("GL Version:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%s",glGetString(GL_VERSION)),nullptr,LABEL_NORMAL);

   label = new FXLabel(matrix,tr("GLU Version:"),nullptr,LABEL_NORMAL|LAYOUT_RIGHT);
   label->setFont(thickfont);
   new FXLabel(matrix,FXString::value("%s",gluGetString(GLU_VERSION)),nullptr,LABEL_NORMAL);

   canvas->makeNonCurrent();
}


// Save OpenGL info to a file
FXbool GLSettingsDialog::saveInformation(const FXString& filename)
{
   GLint intval;
   GLint intvals[2];

   FILE *fp=fopen(filename.text(),"w");
   if (fp) {
      FXGLVisual *glvisual=(FXGLVisual*)canvas->getVisual();
      canvas->makeCurrent();
      fprintf(fp,"Driver Information\n");
      fprintf(fp,"------------------\n");
      fprintf(fp,"\n");
      fprintf(fp,"                       Vendor: %s\n",glGetString(GL_VENDOR));
      fprintf(fp,"                     Renderer: %s\n",glGetString(GL_RENDERER));
      fprintf(fp,"                   GL Version: %s\n",glGetString(GL_VERSION));
      fprintf(fp,"                  GLU Version: %s\n",gluGetString(GLU_VERSION));
      fprintf(fp,"\n");
      fprintf(fp,"Implementation Limits\n");
      fprintf(fp,"---------------------\n");
      fprintf(fp,"\n");
      glGetIntegerv(GL_MAX_VIEWPORT_DIMS, intvals);
      fprintf(fp,"                Viewport Size: %d x %d\n",intvals[0],intvals[1]);
      glGetIntegerv(GL_MAX_TEXTURE_SIZE, &intval);
      fprintf(fp,"                 Texture Size: %d\n",intval);
#if defined(GL_MAX_TEXTURE_UNITS)
      glGetIntegerv(GL_MAX_TEXTURE_UNITS, &intval);
      fprintf(fp,"                Texture Units: %d\n",intval);
#endif
      glGetIntegerv(GL_MAX_LIGHTS, &intval);
      fprintf(fp,"                       Lights: %d\n",intval);
      glGetIntegerv(GL_MAX_CLIP_PLANES, &intval);
      fprintf(fp,"              Clipping Planes: %d\n",intval);
      glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH,&intval);
      fprintf(fp,"              Modelview Stack: %d\n",intval);
      glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH,&intval);
      fprintf(fp,"             Projection Stack: %d\n",intval);
      glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH,&intval);
      fprintf(fp,"              Attribute Stack: %d\n",intval);
#if defined(GL_MAX_VERTEX_ATTRIBS)
      glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &intval);
      fprintf(fp,"            Vertex Attributes: %d\n",intval);
#else
      fprintf(fp,"            Vertex Attributes: -\n");
#endif
#if defined(GL_MAX_VERTEX_UNIFORM_COMPONENTS)
      glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &intval);
      fprintf(fp,"    Vertex Uniform Components: %d\n",intval);
#else
      fprintf(fp,"    Vertex Uniform Components: -\n");
#endif

#if defined(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS)
      glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &intval);
      fprintf(fp,"  Fragment Uniform Components: %d\n",intval);
#else
      fprintf(fp,"  Fragment Uniform Components: -\n");
#endif

      fprintf(fp,"\n");
      fprintf(fp,"Display Mode\n");
      fprintf(fp,"------------\n");
      fprintf(fp,"\n");
      fprintf(fp,"         Hardware Accelerated: %s\n",PRINT_YESNO(glvisual->isAccelerated()));
      fprintf(fp,"             Double Buffering: %s\n",PRINT_YESNO(glvisual->isDoubleBuffer()));
      fprintf(fp,"                  Stereo View: %s\n",PRINT_YESNO(glvisual->isStereo()));
      fprintf(fp,"          Buffer-swap by copy: %s\n",PRINT_YESNO(glvisual->isBufferSwapCopy()));
      fprintf(fp,"                  Color Depth: %d\n",glvisual->getActualRedSize()+glvisual->getActualGreenSize()+glvisual->getActualBlueSize()+glvisual->getActualAlphaSize());
      fprintf(fp,"            Depth Buffer Size: %d\n",glvisual->getActualDepthSize());
      fprintf(fp,"          Stencil Buffer Size: %d\n",glvisual->getActualStencilSize());
      fprintf(fp,"                         RGBA: %d-%d-%d-%d\n",glvisual->getActualRedSize(),glvisual->getActualGreenSize(),glvisual->getActualBlueSize(),glvisual->getActualAlphaSize());
      fprintf(fp,"                   Accum RGBA: %d-%d-%d-%d\n",glvisual->getActualAccumRedSize(),glvisual->getActualAccumGreenSize(),glvisual->getActualAccumBlueSize(),glvisual->getActualAccumAlphaSize());
      fprintf(fp,"                 Multi Sample: %d\n",glvisual->getActualMultiSamples());
      fprintf(fp,"\n");
      fprintf(fp,"Available Extensions\n");
      fprintf(fp,"--------------------\n");
      fprintf(fp,"\n");
      for (FXint i=0;i<extensionlist->getNumItems(); i++) {
         fprintf(fp,"  %s\n",extensionlist->getItemText(i).text());
      }
      canvas->makeNonCurrent();
      fclose(fp);
      return true;
   }
   return false;
}

// Save OpenGL info to file
long GLSettingsDialog::onCmdSave(FXObject*,FXSelector,void*)
{
   FXString filename=FXFileDialog::getSaveFilename(this,tr("Save Information"),FXSystem::getHomeDirectory()+PATHSEPSTRING+"opengl.txt",tr("Text Files (*.txt)\nAll Files(*.*)"));
   if (!filename.empty()) {
      if (FXStat::exists(filename)) {
         if (FXMessageBox::question(this,MBOX_YES_NO,tr("Overwrite File?"),tr("File %s already exists.\nWould you like to overwrite this file?"),filename.text())!=MBOX_CLICKED_YES)
            return 1;
      }
      if (!saveInformation(filename)) {
         FXMessageBox::error(this,MBOX_OK,tr("Write Error"),tr("An error occured trying to write file."));
      }
   }
   return 1;
}

// Destroy
GLSettingsDialog::~GLSettingsDialog()
{
   delete thickfont;
}


#include "LatexAction.h"
#include "../control/Control.h"
#include "../model/Stroke.h"
#include "../model/Layer.h"
#include "../gui/PageView.h"
#include "../gui/XournalView.h"

//some time - clean up these includes
#include <serializing/ObjectOutputStream.h>
#include <serializing/HexObjectEncoding.h>


#include "../control/tools/ImageHandler.h"
#include "../model/TexImage.h"
#include <glib/gstdio.h>

#include "../cfg.h"
#include <glib.h>

LatexAction::LatexAction(gchar* myTex, double tArea)
{
	//this->control = control;

	this->theLatex = myTex;

	this->texfile = g_strconcat(g_get_home_dir(), G_DIR_SEPARATOR_S, CONFIG_DIR,
	                            G_DIR_SEPARATOR_S, "tex", NULL);
	this->texfilefull = g_strconcat(g_get_home_dir(), G_DIR_SEPARATOR_S, CONFIG_DIR,
	                                G_DIR_SEPARATOR_S, "tex.png", NULL);
	printf("%s \n", this->texfile);

	//set up the default positions.
	this->myx = 0;
	this->myy = 0;

	this->texArea = tArea;
}

LatexAction::~LatexAction()
{
	g_free(this->texfile);
	g_free(this->texfilefull);
}

void LatexAction::runCommand()
{
	/*
	 * at some point, I may need to sanitize theLatex
	 */
	printf("Command is being run.\n");
	const gchar* mtex = "mathtex-xournalpp.cgi";
	gchar* mathtex = g_find_program_in_path(mtex);
	if (!mathtex)
	{
		printf("Error: problem finding mathtex. Doing nothing...\n");
		return;
	}
	printf("Found mathtex in your path! Area is %f\n",this->texArea);
	g_free(mathtex);
	gchar* command = NULL;
	//can change font colour later with more features
	const gchar* fontcolour = "black";
	//dpi 300 is a good balance
	gchar* texres = "";
	if (this->texArea < 1000)
	{
		texres = "300";
	}
	else if (this->texArea < 4000)
	{
		texres = "400";
	}
	else if (this->texArea < 8000)
	{
		texres = "500";
	}
	else if (this->texArea < 16000)
	{
		texres = "600";
	}
	else if (this->texArea < 32000)
	{
		texres = "800";
	}
	else
	{
		texres = "1000";
		
	}
	command = g_strdup_printf(
	              "%s -m 0 \"\\png\\usepackage{color}\\color{%s}\\dpi{%s}\\%s %s\" -o %s",
	              mtex, strlen(fontcolour) ? fontcolour : "black",
		      texres,
	              "normalsize",
	              g_strescape(this->theLatex, NULL), this->texfile);

	gint rt = 0;
	void(*texhandler)(int) = signal(SIGCHLD, SIG_DFL);
	gboolean success = g_spawn_command_line_sync(command, NULL, NULL, &rt, NULL);
	signal(SIGCHLD, texhandler);
	if (!success)
	{
		printf("Latex Command execution failed.\n");
		return;
	}
	g_free(command);
	printf("Tex command: \"%s\" was successful; in file %s.\n", this->theLatex,
	       this->texfilefull);

}


gchar* LatexAction::getFileName()
{
	//gets the filename for our image
	return this->texfilefull;
}

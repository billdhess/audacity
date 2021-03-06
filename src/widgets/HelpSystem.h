/**********************************************************************

  Audacity: A Digital Audio Editor

  HelpSystem.h

  Jimmy Johnson
  James Crook

**********************************************************************/

#ifndef __AUDACITY_HELPSYSTEM__
#define __AUDACITY_HELPSYSTEM__

#include "../Audacity.h"

#include <wx/defs.h>
#include "wxPanelWrapper.h" // to inherit

class AudacityProject;

/** @brief Class which contains static methods and data needed for implementing
 * help buttons
 *
 * This class should be the only place in the codebase where the location of
 * the online copy of the Audacity manual is stored, so that it can be 
 * changed if required
 */
class HelpSystem
{
public:
   /// Displays cutable information in a text ctrl, with an OK button.
   static void ShowInfoDialog( wxWindow *parent,
                     const wxString &dlogTitle,
                     const wxString &shortMsg,
                     const wxString &message, 
                     const int xSize, const int ySize);

   /// Displays a NEW window with wxHTML help.
   /// @param HtmlText Either the literal HTML code to go into the window,
   /// or the name of the file to read said HTML code from (see below).
   /// @param bIsFile If true, treat HtmlText argument as a file name, if false
   /// (default), then it is the HTML code to display.
   /// @param bModal Whether the resulting window should be modal or not.
   /// Default is modeless dialogue
   static void ShowHtmlText( wxWindow * pParent, 
                   const wxString &Title,
                   const wxString &HtmlText,
                   bool bIsFile = false,
                   bool bModal = false);

   /// Displays a file in your browser, if it's available locally,
   /// OR else links to the internet. Generally using this outside this class
   /// is depreciated in favour of the "smarter" overload below, unless there
   /// is a good reason for using this form.
   /// @param localFileName Name and path of the file on the local machine
   /// file system to be opened. file.name#anchor syntax is allowed, and therefore
   /// file names containing a '#' are not (on any platform).
   /// @param bModal Whether the resulting dialogue should be modal or not.
   /// Default is modeless dialogue
   /// @param alwaysDefaultBrowser Force use of default web browser.
   /// Default allows built in browser for local files.
   static void ShowHelp(wxWindow *parent,
                     const wxString &localFileName,
                     const wxString &remoteURL,
                     bool bModal = false,
                     bool alwaysDefaultBrowser = false);

   /// Displays a page from the Audacity manual  in your browser, if
   /// it's available locally, OR else links to the internet.
   /// @param PageName The name of the manual page to display as it is in
   /// _development version_ of the manual (i.e. in MediaWiki), _not_ the
   /// converted file name used for offline and released manuals.
   /// @param bModal Whether the resulting dialogue should be modal or not.
   /// Default is modeless dialogue
   static void ShowHelp(wxWindow *parent,
                     const wxString &PageName,
                     bool bModal = false);

   /// Hostname (domain name including subdomain) of the server on which the
   /// online help is available
   static const wxString HelpHostname;

   /// URL path on the help server to the root directory of the manual.
   /// index and quick_help are here in the on-line release manual.
   /// Must both start and end with '/' characters.
   static const wxString HelpServerHomeDir;

   /// Path to sub-directory where the manual pages are located.
   /// index and quick_help are here only in the alpha manual.
   /// Must both start and end with '/' characters.
   static const wxString HelpServerManDir;

   /// Sub-directory for local help pages (but not index.html
   /// or quick_help.html)
   /// Must both start and end with '/' characters.
   static const wxString LocalHelpManDir;

   /// The string which is appended to the development manual page name in order
   /// obtain the file name in the local and release web copies of the manual
   static const wxString ReleaseSuffix;

};

class ShuttleGui;

/** @brief Class which makes a dialog for displaying quick fixes to common issues.
 *
 * This class originated with the 'Stuck in a mode' problem, where far too many
 * users get into a mode without realising, and don't know how to get out.
 * It is a band-aid, and we should do more towards a full and proper solution
 * where there are fewer special modes, and they don't persisit.
 */
class QuickFixDialog : public wxDialogWrapper
{
public: 
   QuickFixDialog(wxWindow * pParent);
   void Populate();
   void PopulateOrExchange(ShuttleGui & S);
   void AddStuck( ShuttleGui & S, bool & bBool, wxString Pref,  wxString Prompt, wxString Help );

   void OnOk(wxCommandEvent &event);
   void OnCancel(wxCommandEvent &event);
   void OnHelp(wxCommandEvent &event);
   void OnFix(wxCommandEvent &event);

   wxString StringFromEvent( wxCommandEvent &event );

   int mItem;
   bool mbSyncLocked;
   bool mbInSnapTo;
   bool mbSoundActivated;
   DECLARE_EVENT_TABLE()
};

#endif // __AUDACITY_HELPSYSTEM__

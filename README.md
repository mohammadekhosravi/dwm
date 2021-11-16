## MamadDWM

### Optional Dependencies: 
1. picom

   Picom is a compositor for X, and it is used for transparency and some other stuff that I don't know.
2. nitrogen

   Nitrogen is used for setting background image for the first time and restoring it on each new session.

   **Note that I patch DWM in a way that you can define all the thing that you need to start with DWM inside config file itself. Thanks to [this](https://dwm.suckless.org/patches/cool_autostart/).**

   *Remove the line invole picom and nitrogen if you don't want them.*
**********
### Patches:
1. [activatetagindicatorbar](https://dwm.suckless.org/patches/activetagindicatorbar/):

   A simple indicator above tag name instead of default square one.
2. [alpha](https://dwm.suckless.org/patches/alpha/):

   Transparency for topbar.
3. [restartsig](https://dwm.suckless.org/patches/restartsig/):

   Restart DWM with one key combination(see config file for which combination).
4. [cool autostart](https://dwm.suckless.org/patches/cool_autostart/): 

   Autostart program or scripts with DWM startup.
5. [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/):

   This patch prevents dwm from drawing tags with no active window (i.e. vacant) on the bar.
6. [sticky](https://dwm.suckless.org/patches/sticky/):

   Press MODKEY+s (default) to make a client 'sticky'. A sticky client is visible on all tags.
7. [pertag](https://dwm.suckless.org/patches/pertag/):

   This patch keeps layout, mwfact, barpos and nmaster per tag.
8. [functionalgaps](https://dwm.suckless.org/patches/functionalgaps/):

   Gaps between windows.</br>
   **Compatible with _pertag_.**
9. [shift tools](https://dwm.suckless.org/patches/shift-tools/):

   A group of functions that shift.
10. [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/):

   Cycle through all layouts.

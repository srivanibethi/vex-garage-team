# 95070E-2024-2025


this codebase is based on VSCode ``VEX Robotics Extension``. before you start to code, you need to do one-time setup as below. 

## set up

##### for macOS user

go to top menu ``Terminal`` -> ``New Terminal`` and type the command:

```
$ cp -r vscode_mac .vscode
```

##### for windows user

go to top menu ``Terminal`` -> ``New Terminal`` and type the command:

```
$ xcopy "vscode_win"  ".vscode"  /E /H /C /I
```


## one more step

after the above setup, you need to ``close``/``reopen`` VSCode. otherwise, you can not see ``VEX`` build buttons on the bottom menu.


## AUTON code
To run the autonomous code during a match:
    - The competition switch or controller will trigger the autonomous routine automatically.
    - The Competition.autonomous() registration in main() connects your autonomous() function to the competition system.
To run different autonomous routines:
    - Uncomment the routine you want to use (eg:AWPRed, AWPBlue, Red, or Blue)
    - Comment out the others
To test autonomous without a competition switch:
    - In the VEX V5 Controller, hold the "A" button while turning on the brain to force it into autonomous mode.
    - OR in the programming interface simulator, you can select "Run Autonomous" mode.

name: Build PS2 Game

on:
  push:
    branches: [ main, master ]
  pull_request:
    branches: [ main, master ]

jobs:
  build:
    runs-on: ubuntu-latest
    container:
      image: h4570/tyra:latest

    steps:
    - uses: actions/checkout@v3

    - name: Build Project
      run: |
        cd $GITHUB_WORKSPACE
        make clean
        make

    - name: Upload Build Artifacts
      uses: actions/upload-artifact@v3
      with:
        name: ps2-game-build
        path: |
          *.elf
          *.iso
          build/
        retention-days: 30

    - name: Create Release
      if: startsWith(github.ref, 'refs/tags/')
      uses: softprops/action-gh-release@v1
      with:
        files: |
          *.elf
          *.iso
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}

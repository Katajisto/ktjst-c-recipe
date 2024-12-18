
{{if .Variables.INCLUDE_LIBS | has "raylib"}} 
mkdir vendor
cd vendor
git clone https://github.com/raysan5/raylib.git
cd raylib
git checkout tags/5.5
rm -rf .git
echo "Downloaded raylib!"
cd ..
cd ..
{{ end }}

echo "Init done."
git init

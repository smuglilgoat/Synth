# Synth

Travaux pratiques de synthèse d'image avec OpenGL, du pipeline fixe aux shaders modernes.

## Contenu

| Dossier | Sujet |
| --- | --- |
| `Synth_TP1` | Ouverture d'une fenêtre GLUT |
| `synth_tp2` | Primitives et transformations |
| `Synth_TP3` | Translations et changements d'échelle |
| `Synth_TP4` | Premiers shaders GLSL (GLEW, freeglut) |
| `synth_tp5` | Pipeline shader avec GLEW |
| `synth_tp6` | Passage à GLFW, shaders et VBO |
| `synth_tp7` | Triangle strip et caméra |
| `synth_tp8` | Textures |
| `opengl_tp` | Projet OpenGL moderne compilable sous Linux (GLFW, GLAD, GLM, stb) |

## Compilation

Les TPs 1 à 8 sont prévus pour Windows : chaque dossier contient un `compil.bat` et les DLL nécessaires (`freeglut.dll`, `glew32.dll`, `glfw3.dll`).

```bat
cd Synth_TP1
compil.bat
```

`opengl_tp` fournit un script de compilation Linux :

```bash
cd opengl_tp
./build.sh
./a.out
```

Dépendances : OpenGL, GLU, freeglut, GLEW, GLFW, GLM et stb_image. Les TPs 4 et suivants chargent leurs shaders depuis les fichiers du dossier (`.fragmentshader`/`.vertexshader` ou `.vs`/`.fs`).

## Notes

- `pdf/TP7.pdf` accompagne le TP sur la caméra.
- `opengl_tp/img/peppers.png` est la texture utilisée par l'exemple de texturage.

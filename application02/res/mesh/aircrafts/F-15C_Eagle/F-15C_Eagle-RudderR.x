xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header {
 1;
 0;
 1;
}

Mesh {
  60;
 1.725470;3.057290;-6.099960;,
 1.745570;3.057290;-5.672330;,
 1.722420;3.057290;-5.653190;,
 1.722420;3.057290;-5.653190;,
 1.699270;3.057290;-5.672330;,
 1.725470;3.057290;-6.099960;,
 1.681510;0.624770;-5.119140;,
 1.699270;3.057290;-5.672330;,
 1.722420;3.057290;-5.653190;,
 1.722420;3.057290;-5.653190;,
 1.722510;0.624770;-5.100010;,
 1.681510;0.624770;-5.119140;,
 1.727900;0.624770;-6.013100;,
 1.681510;0.624770;-5.119140;,
 1.722510;0.624770;-5.100010;,
 1.722510;0.624770;-5.100010;,
 1.763510;0.624770;-5.119140;,
 1.727900;0.624770;-6.013100;,
 1.763510;0.624770;-5.119140;,
 1.722510;0.624770;-5.100010;,
 1.722420;3.057290;-5.653190;,
 1.722420;3.057290;-5.653190;,
 1.745570;3.057290;-5.672330;,
 1.763510;0.624770;-5.119140;,
 1.745570;3.057300;-5.672340;,
 1.763510;0.624780;-5.119140;,
 1.727900;0.624770;-6.013100;,
 1.727900;0.624770;-6.013100;,
 1.725470;3.057290;-6.099980;,
 1.745570;3.057300;-5.672340;,
 1.727900;0.624770;-6.013100;,
 1.681500;0.624780;-5.119140;,
 1.699270;3.057300;-5.672340;,
 1.699270;3.057300;-5.672340;,
 1.725470;3.057290;-6.099980;,
 1.727900;0.624770;-6.013100;,
 1.725470;3.057290;-6.099980;,
 1.699270;3.057300;-5.672340;,
 1.722420;3.057300;-5.656190;,
 1.722420;3.057300;-5.656190;,
 1.745570;3.057300;-5.672340;,
 1.725470;3.057290;-6.099980;,
 1.763510;0.624780;-5.119140;,
 1.745570;3.057300;-5.672340;,
 1.722420;3.057300;-5.656190;,
 1.722420;3.057300;-5.656190;,
 1.722510;0.624780;-5.102990;,
 1.763510;0.624780;-5.119140;,
 1.727900;0.624770;-6.013100;,
 1.763510;0.624780;-5.119140;,
 1.722510;0.624780;-5.102990;,
 1.722510;0.624780;-5.102990;,
 1.681500;0.624780;-5.119140;,
 1.727900;0.624770;-6.013100;,
 1.681500;0.624780;-5.119140;,
 1.722510;0.624780;-5.102990;,
 1.722420;3.057300;-5.656190;,
 1.722420;3.057300;-5.656190;,
 1.699270;3.057300;-5.672340;,
 1.681500;0.624780;-5.119140;;
 20;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;12,13,14;,
 3;15,16,17;,
 3;18,19,20;,
 3;21,22,23;,
 3;24,25,26;,
 3;27,28,29;,
 3;30,31,32;,
 3;33,34,35;,
 3;36,37,38;,
 3;39,40,41;,
 3;42,43,44;,
 3;45,46,47;,
 3;48,49,50;,
 3;51,52,53;,
 3;54,55,56;,
 3;57,58,59;;

 MeshMaterialList {
  15;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;
  Material {
   0.913725;0.913725;0.913725;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.564706;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.564706;0.564706;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   1.000000;0.682353;0.682353;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.564706;1.000000;0.564706;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   1.000000;1.000000;0.356863;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   1.000000;0.909804;0.850980;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.776471;0.364706;0.207843;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.905882;0.733333;0.588235;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   1.000000;0.070588;0.070588;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.972549;0.972549;0.972549;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.913725;0.913725;0.913725;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
  Material {
   0.913725;0.913725;0.913725;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
  }
 }

 MeshNormals {
  60;
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.524751;-0.190952;-0.829562;,
  0.627126;-0.177078;-0.758523;,
  0.524751;-0.190952;-0.829562;,
  0.234534;-0.217193;-0.947534;,
  0.000001;-0.221749;-0.975104;,
  0.524751;-0.190952;-0.829562;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.524747;-0.190990;-0.829556;,
  0.000001;-0.221749;-0.975104;,
  -0.234530;-0.217209;-0.947531;,
  -0.524747;-0.190990;-0.829556;,
  -0.627121;-0.177123;-0.758516;,
  -0.524747;-0.190990;-0.829556;,
  0.960444;0.069402;0.269688;,
  0.892730;0.106172;0.437905;,
  0.999058;-0.001181;-0.043377;,
  0.999058;-0.001181;-0.043377;,
  0.998897;-0.000679;-0.046950;,
  0.960444;0.069402;0.269688;,
  -0.998396;-0.003837;-0.056493;,
  -0.895500;0.104905;0.432521;,
  -0.963052;0.067613;0.260690;,
  -0.963052;0.067613;0.260690;,
  -0.998124;-0.003181;-0.061151;,
  -0.998396;-0.003837;-0.056493;,
  -0.000000;1.000000;-0.000023;,
  0.000016;1.000000;-0.000022;,
  -0.000000;1.000000;-0.000023;,
  -0.000000;1.000000;-0.000023;,
  -0.000016;1.000000;-0.000023;,
  -0.000000;1.000000;-0.000023;,
  0.744514;0.152293;0.650004;,
  0.960444;0.069402;0.269688;,
  0.204237;0.218514;0.954222;,
  0.000020;0.223983;0.974593;,
  0.000040;0.221756;0.975102;,
  0.463353;0.198504;0.863655;,
  0.000000;-1.000000;0.000011;,
  0.000004;-1.000000;0.000011;,
  0.000000;-1.000000;0.000011;,
  0.000000;-1.000000;0.000011;,
  -0.000004;-1.000000;0.000011;,
  0.000000;-1.000000;0.000011;,
  -0.463320;0.198476;0.863679;,
  0.000040;0.221756;0.975102;,
  0.000020;0.223983;0.974593;,
  -0.204187;0.218502;0.954235;;
  -0.963052;0.067613;0.260690;,
  -0.746785;0.151693;0.647535;,

  20;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  3;12,13,14;,
  3;15,16,17;,
  3;18,19,20;,
  3;21,22,23;,
  3;24,25,26;,
  3;27,28,29;,
  3;30,31,32;,
  3;33,34,35;,
  3;36,37,38;,
  3;39,40,41;,
  3;42,43,44;,
  3;45,46,47;,
  3;48,49,50;,
  3;51,52,53;,
  3;54,55,56;,
  3;57,58,59;;
 }

 MeshTextureCoords {
  60;
  0.772300;1.250530;,
  0.769550;1.244990;,
  0.648310;1.249800;,
  0.648310;1.249800;,
  0.769550;1.256070;,
  0.772300;1.250530;,
  0.770500;1.245370;,
  0.583140;1.245360;,
  0.583140;1.250080;,
  0.583140;1.250080;,
  0.770500;1.250090;,
  0.770500;1.245370;,
  0.648310;1.249800;,
  0.769550;1.256070;,
  0.772300;1.250530;,
  0.772300;1.250530;,
  0.769550;1.244990;,
  0.648310;1.249800;,
  0.770500;1.254810;,
  0.770500;1.250090;,
  0.583140;1.250080;,
  0.583140;1.250080;,
  0.583140;1.254790;,
  0.770500;1.254810;,
  0.270570;1.942900;,
  0.242210;1.818180;,
  0.288050;1.818180;,
  0.288050;1.818180;,
  0.292500;1.942900;,
  0.270570;1.942900;,
  0.244850;1.564980;,
  0.244850;1.610820;,
  0.369570;1.582450;,
  0.369570;1.582450;,
  0.369570;1.560530;,
  0.244850;1.564980;,
  0.648310;1.249800;,
  0.769550;1.256070;,
  0.772300;1.250530;,
  0.772300;1.250530;,
  0.769550;1.244990;,
  0.648310;1.249800;,
  0.771230;1.255540;,
  0.583140;1.255530;,
  0.583140;1.250440;,
  0.583140;1.250440;,
  0.771230;1.250450;,
  0.771230;1.255540;,
  0.648310;1.249800;,
  0.769550;1.244990;,
  0.772300;1.250530;,
  0.772300;1.250530;,
  0.769550;1.256070;,
  0.648310;1.249800;,
  0.771230;1.245370;,
  0.771230;1.250450;,
  0.583140;1.250440;,
  0.583140;1.250440;;
  0.583140;1.245360;,
  0.771230;1.245370;,
 }
}

//----- (10004420) --------------------------------------------------------
int MOM_POST_dh_setup_vector_conversion(int a1, const void *a2, int a3, int a4, int a5, int a6, int a7, int a8, const void *a9)
{
  dword_1000C330 = *(_DWORD *)a3;
  dword_1000C334 = *(_DWORD *)(a3 + 4);
  dword_1000C338 = *(_DWORD *)(a3 + 8);
  dword_1000C33C = *(_DWORD *)(a3 + 12);
  dword_1000C340 = *(_DWORD *)(a3 + 16);
  dword_1000C344 = *(_DWORD *)(a3 + 20);
  dword_1000C0B0 = *(_DWORD *)a5;
  dword_1000C0B4 = *(_DWORD *)(a5 + 4);
  dword_1000C0B8 = *(_DWORD *)(a5 + 8);
  dword_1000C0BC = *(_DWORD *)(a5 + 12);
  dword_1000C0C0 = *(_DWORD *)(a5 + 16);
  v12 = *(_DWORD *)(a5 + 20);
  v108 = 0;
  dword_1000C0C4 = v12;
  UF_VEC3_copy(a4, &v104);
  v10 = a6;
  UF_VEC3_copy(a6, &v101);
  UF_VEC3_copy(a8, &v91);
  dbl_1000C348 = 0.0;
  dbl_1000C350 = 0.0;
  dbl_1000C358 = 0.0;
  byte_1000C378 = 0;
  dword_1000C1C0 = (int)&unk_1000C128;
  dbl_1000C360 = 0.0;
  memcpy(&unk_1000C128, a9, 0x98u);
  dbl_1000C368 = 0.0;
  dbl_1000C370 = 0.0;
  dbl_1000C010 = dbl_1000C130;
  memcpy(&dbl_1000C258, a2, 0x60u);
  dbl_1000C328 = 0.0;
  dbl_1000C320 = 0.0;
  dbl_1000C0D0 = 0.0;
  dbl_1000C0C8 = 0.0;
  dbl_1000C250 = 0.0;
  v11 = a4;
  dbl_1000C248 = 0.0;
  dbl_1000C108 = 0.0;
  dbl_1000C100 = 0.0;
  UF_VEC3_unitize(a4, LODWORD(dbl_1000C130), HIDWORD(dbl_1000C130), &v109, &dbl_1000C0D8);
  UF_VEC3_unitize(v10, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v109, &dbl_1000C110);
  dword_1000C2C8 = 0;
  dword_1000C2F0 = 0;
  dword_1000C2CC = 0;
  dword_1000C2F4 = 0;
  dword_1000C2D0 = 0;
  dword_1000C2F8 = 0;
  dword_1000C2D4 = 0;
  dword_1000C2FC = 0;
  dword_1000C2D8 = 0;
  dword_1000C300 = 0;
  dword_1000C2DC = 0;
  dword_1000C304 = 0;
  dword_1000C2E0 = 0;
  dword_1000C308 = 0;
  dword_1000C2E4 = 0;
  dword_1000C30C = 0;
  dword_1000C2E8 = 0;
  dword_1000C310 = 0;
  dword_1000C2EC = 0;
  dword_1000C314 = 0;
  v9 = *(_DWORD *)dword_1000C1C0;
  v13 = *(_DWORD *)dword_1000C1C0 == 1;
  byte_1000C019 = 1;
  byte_1000C01A = 1;
  if ( !v13 && v9 != 2 && v9 != 3 )
    return 2;
  UF_VEC3_is_parallel(&v104, &v101, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v111);
  v112 = v111 != 0;
  UF_VEC3_is_parallel(&v104, &v91, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v111);
  BYTE3(a2) = v111 != 0;
  UF_VEC3_is_parallel(&v101, &v91, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v111);
  BYTE3(a9) = v111 != 0;
  if ( !BYTE3(a2) )
  {
    v113 = v109;
    UF_VEC3_cross(&v104, &v91, &v94);
    UF_VEC3_unitize(&v94, COERCE_UNSIGNED_INT64(1.0e-10), COERCE_UNSIGNED_INT64(1.0e-10) >> 32, &v113, &v94);
  }
  UF_VEC3_cross(&v104, &v101, &v77);
  UF_VEC3_is_parallel(&v77, &v91, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v111);
  byte_1000C018 = v111 != 0;
  if ( byte_1000C378 )
  {
    printf("\n\n======================================================================\n");
    printf("Is_orthogonal_case = %d, ", byte_1000C018);
    if ( dword_1000C1C0 == 2 )
    {
      printf("is_5_axis_dual_table\n");
    }
    else
    {
      if ( dword_1000C1C0 == 1 )
        printf("is_5_axis_dual_head\n");
      else
        printf("is_5_axis_head_table\n");
    }

    printf("primary=(%f,%f,%f)\n", *(double *)v11, *(double *)(v11 + 8), *(double *)(v11 + 16));
    v14 = a3;
    printf("primary_machine_center=(%f,%f,%f)\n", *(double *)a3, *(double *)(a3 + 8), *(double *)(a3 + 16));
    printf("secondary=(%f,%f,%f)\n", *(double *)v10, *(double *)(v10 + 8), *(double *)(v10 + 16));
    printf("secondary_machine_center=(%f,%f,%f)\n", *(double *)a5, *(double *)(a5 + 8), *(double *)(a5 + 16));
    printf("tool_machine_center=(%f,%f,%f)\n", *(double *)a7, *(double *)(a7 + 8), *(double *)(a7 + 16));
    printf("tool_vector=(%f,%f,%f)\n", *(double *)a8, *(double *)(a8 + 8), *(double *)(a8 + 16));
    printf(
      "Mcsys= (%f,%f,%f) (%f,%f,%f) (%f,%f,%f)  (%f,%f,%f)\n",
      *(_QWORD *)&dbl_1000C258,
      *(_QWORD *)&dbl_1000C260,
      *(_QWORD *)&dbl_1000C268,
      *(_QWORD *)&dbl_1000C270,
      *(_QWORD *)&dbl_1000C278,
      *(_QWORD *)&dbl_1000C280,
      *(_QWORD *)&dbl_1000C288,
      *(_QWORD *)&dbl_1000C290,
      *(_QWORD *)&dbl_1000C298,
      *(_QWORD *)&dbl_1000C2A0,
      *(_QWORD *)&dbl_1000C2A8,
      *(_QWORD *)&dbl_1000C2B0);
  }
  else
  {
    v14 = a3;
  }
  v15 = *(_DWORD *)dword_1000C1C0 == 3;
  dword_1000C318 = -1;
  if ( !v15 )
  {
LABEL_22:
    if ( v112 )
    {
      v16 = 0.0;
    }
    else
    {
      v113 = v109;
      UF_VEC3_cross(&v104, &v101, &v94);
      UF_VEC3_unitize(&v94, COERCE_UNSIGNED_INT64(1.0e-10), &v113, &v94);
      UF_VEC3_angle_between(&v104, &v101, &v94, &v113);
      v16 = v113;
    }
    dbl_1000C368 = v16;
    if ( BYTE3(a9) )
    {
      printf("WARNING: Tool axis is parallelled with secondary axis that may cause unresolved rotaries");
      v18 = 0.0;
    }
    else
    {
      if ( fabs(dbl_1000C368) <= dbl_1000C010 )
      {
        v113 = v109;
        UF_VEC3_cross(&v101, &v91, &v94);
        UF_VEC3_unitize(&v94, COERCE_UNSIGNED_INT64(1.0e-10), &v113, &v94);
        if ( fabs(v109) <= dbl_1000C010 )
          return 3;
      }
      if ( byte_1000C018 )
      {
        v113 = v109;
        UF_VEC3_cross(&v101, &v91, &v85);
        UF_VEC3_unitize(&v85, COERCE_UNSIGNED_INT64(1.0e-10), &v113, &v85);
        UF_VEC3_angle_between(&v101, &v91, &v85, &v113);
      }
      else
      {
        UF_VEC3_angle_between(&v101, &v91, &v94, &v113);
      }
      v18 = v113;
    }
    dbl_1000C370 = v18;
    v19 = a5;
    v20 = *(double *)&v104 * 1000000.0 + *(double *)v14;
    v74 = *(double *)v14 - *(double *)&v104 * 1000000.0;
    v95 = v101 * 1000000.0 + *(double *)a5;
    v98 = *(double *)a5 - v101 * 1000000.0;
    v61 = v20;
    v67 = v95;
    v64 = v74;
    v70 = v98;
    v21 = *(double *)&v105 * 1000000.0 + *(double *)(v14 + 8);
    v75 = *(double *)(v14 + 8) - *(double *)&v105 * 1000000.0;
    v96 = v102 * 1000000.0 + *(double *)(a5 + 8);
    v99 = *(double *)(a5 + 8) - v102 * 1000000.0;
    v62 = v21;
    v68 = v96;
    v65 = v75;
    v71 = v99;
    v22 = *(double *)&v106 * 1000000.0 + *(double *)(v14 + 16);
    v76 = *(double *)(v14 + 16) - *(double *)&v106 * 1000000.0;
    v97 = v103 * 1000000.0 + *(double *)(a5 + 16);
    v100 = *(double *)(a5 + 16) - v103 * 1000000.0;
    v63 = v22;
    v69 = v97;
    v66 = v76;
    v72 = v100;
    if ( sub_100041E0((int)&v61, (int)&v67, (int)&v60, (int)&v78, (int)&v110, (int)&v107) )
      return 5;
    UF_VEC3_distance(&v60, &v78, &dbl_1000C348);
    if ( dbl_1000C348 <= dbl_1000C010 )
    {
      v23 = 0.0;
    }
    else
    {
      UF_VEC3_sub(&v78, &v60, &v77);
      UF_VEC3_dot(&v77, &v94, &v113);
      if ( v113 >= 0.0 )
        goto LABEL_47;
      v23 = -dbl_1000C348;
    }
    dbl_1000C348 = v23;
LABEL_47:
    UF_VEC3_distance(&v78, v14, &dbl_1000C350);
    if ( dbl_1000C350 <= dbl_1000C010 )
    {
      v24 = 0.0;
    }
    else
    {
      UF_VEC3_sub(&v78, v14, &v77);
      UF_VEC3_dot(&v77, &v104, &v113);
      if ( v113 >= 0.0 )
        goto LABEL_52;
      v24 = -dbl_1000C350;
    }
    dbl_1000C350 = v24;
LABEL_52:
    v26 = v101 * 1000000.0 + *(double *)v19;
    v27 = *(double *)v19;
    v25 = a7;
    v74 = v27 - v101 * 1000000.0;
    v95 = v91 * 1000000.0 + *(double *)a7;
    v98 = *(double *)a7 - v91 * 1000000.0;
    v61 = v26;
    v67 = v95;
    v64 = v74;
    v70 = v98;
    v28 = v102 * 1000000.0 + *(double *)(a5 + 8);
    v75 = *(double *)(a5 + 8) - v102 * 1000000.0;
    v96 = v92 * 1000000.0 + *(double *)(a7 + 8);
    v99 = *(double *)(a7 + 8) - v92 * 1000000.0;
    v62 = v28;
    v68 = v96;
    v65 = v75;
    v71 = v99;
    v29 = v103 * 1000000.0 + *(double *)(a5 + 16);
    v76 = *(double *)(a5 + 16) - v103 * 1000000.0;
    v97 = v93 * 1000000.0 + *(double *)(a7 + 16);
    v100 = *(double *)(a7 + 16) - v93 * 1000000.0;
    v63 = v29;
    v69 = v97;
    v66 = v76;
    v72 = v100;
    if ( sub_100041E0((int)&v61, (int)&v67, (int)&v60, (int)&v78, (int)&v110, (int)&v107) )
      return 5;
    UF_VEC3_distance(&v60, &v78, &dbl_1000C358);
    if ( dbl_1000C358 <= dbl_1000C010 )
    {
      v30 = 0.0;
    }
    else
    {
      UF_VEC3_sub(&v78, &v60, &v77);
      UF_VEC3_dot(&v77, &v94, &v110);
      if ( v110 >= 0.0 )
        goto LABEL_59;
      v30 = -dbl_1000C358;
    }
    dbl_1000C358 = v30;
LABEL_59:
    UF_VEC3_distance(&v78, v25, &dbl_1000C360);
    if ( dbl_1000C360 <= dbl_1000C010 )
    {
      v31 = 0.0;
    }
    else
    {
      UF_VEC3_sub(&v78, v25, &v77);
      UF_VEC3_dot(&v77, &v101, &v110);
      if ( v110 >= 0.0 )
      {
LABEL_64:
        v32 = *(_DWORD *)v14;
        v33 = *(_DWORD *)(v14 + 4);
        v110 = v109;
        v34 = *(_DWORD *)(v14 + 8);
        v49 = v32;
        v35 = *(_DWORD *)(v14 + 12);
        v50 = v33;
        v36 = *(_DWORD *)(v14 + 16);
        v51 = v34;
        v37 = *(_DWORD *)(v14 + 20);
        v52 = v35;
        v53 = v36;
        v54 = v37;
        UF_VEC3_cross(&v104, &v101, &v55);
        UF_VEC3_unitize(&v55, COERCE_UNSIGNED_INT64(1.0e-10), &v110, &v55);
        v110 = v109;
        *(_QWORD *)&v57 = v104;
        *(_QWORD *)&v58 = v105;
        *(_QWORD *)&v59 = v106;
        UF_VEC3_cross(&v104, &v55, &v56);
        UF_VEC3_unitize(&v56, COERCE_UNSIGNED_INT64(1.0e-10), &v110, &v56);
        sub_10002150((int)&v49, a1, (int)&unk_1000C1C8);
        sub_10003080((int)&unk_1000C1C8, (int)&dbl_1000C030);
        dbl_1000C0F8 = sin(dbl_1000C368);
        dbl_1000C2B8 = sin(dbl_1000C370);
        dbl_1000C2C0 = cos(dbl_1000C368);
        dbl_1000C0F0 = cos(dbl_1000C370);
        if ( byte_1000C378 )
          printf(
            "A1=%f,D1=%f,Alpha1=%f,A2=%f,D2=%f,Alpha2=%f\n",
            *(_QWORD *)&dbl_1000C348,
            *(_QWORD *)&dbl_1000C350,
            dbl_1000C368 * 57.29577951308235,
            *(_QWORD *)&dbl_1000C358,
            *(_QWORD *)&dbl_1000C360,
            dbl_1000C370 * 57.29577951308235);
        if ( *(_DWORD *)dword_1000C1C0 == 2 )
        {
          v38 = *(_DWORD *)(v25 + 8);
          v39 = *(_DWORD *)(v25 + 4);
          v79 = *(_DWORD *)v25;
          v40 = *(_DWORD *)(v25 + 12);
          v80 = v39;
          v41 = *(_DWORD *)(v25 + 16);
          v81 = v38;
          v42 = *(_DWORD *)(v25 + 20);
          v82 = v40;
          v83 = v41;
          v84 = v42;
          v43 = *(_DWORD *)(a8 + 4);
          v85 = *(_DWORD *)a8;
          v44 = *(_DWORD *)(a8 + 8);
          v86 = v43;
          v45 = *(_DWORD *)(a8 + 12);
          v87 = v44;
          v46 = *(_DWORD *)(a8 + 16);
          v88 = v45;
          v47 = *(_DWORD *)(a8 + 20);
          v89 = v46;
          v90 = v47;
          sub_10003400(&v79, (int)&v73, (int)&v96);
          if ( byte_1000C378 )
          {
            printf(
              "Init_T1[0], Init_T2[0] = (%f,%f)\n",
              dbl_1000C320 * 57.29577951308235,
              dbl_1000C0C8 * 57.29577951308235);
            printf(
              "Init_T1[1], Init_T2[1] = (%f,%f)\n",
              dbl_1000C328 * 57.29577951308235,
              dbl_1000C0D0 * 57.29577951308235);
          }
        }
        result = 0;
        byte_1000C019 = 0;
        return result;
      }
      v31 = -dbl_1000C360;
    }
    dbl_1000C360 = v31;
    goto LABEL_64;
  }
  UF_MTX3_x_vec(&unk_10009878, &v98);
  UF_MTX3_y_vec(&unk_10009878, &v74);
  UF_MTX3_z_vec(&unk_10009878, &v85);
  UF_VEC3_is_equal(a8, &v85, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &a3);
  if ( !a3 )
  {
    UF_VEC3_is_equal(a8, &v74, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &a2);
    UF_VEC3_is_equal(&v104, &v85, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v108);
    if ( !byte_1000C018 && BYTE3(a9) && a2 && v108 )
    {
      dword_1000C318 = 3;
      UF_MTX3_vec_multiply_t(&dbl_1000C0D8, &unk_10009908, &dbl_1000C0D8);
      UF_MTX3_vec_multiply_t(&dbl_1000C110, &unk_10009908, &dbl_1000C110);
      if ( byte_1000C378 )
      {
        printf("Sulzer case:\n");
        printf(
          "local PrimaryAxis=(%f,%f,%f)\n",
          *(_QWORD *)&dbl_1000C0D8,
          *(_QWORD *)&dbl_1000C0E0,
          *(_QWORD *)&dbl_1000C0E8);
        printf(
          "local SecondaryAxis=(%f,%f,%f)\n",
          *(_QWORD *)&dbl_1000C110,
          *(_QWORD *)&dbl_1000C118,
          *(_QWORD *)&dbl_1000C120);
      }
      goto LABEL_22;
    }
    return 2;
  }
  UF_VEC3_is_equal(a4, &v98, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &a5);
  UF_VEC3_is_equal(v10, &v74, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &a9);
  UF_VEC3_is_equal(v10, &v85, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &a2);
  if ( a5 && a9 )
  {
    result = v108;
    dword_1000C318 = 0;
    byte_1000C019 = 0;
  }
  else
  {
    if ( a2 )
    {
      result = v108;
      dword_1000C318 = 1;
      byte_1000C019 = 0;
    }
    else
    {
      v108 = 2;
      result = 2;
      byte_1000C019 = 0;
    }
  }
  return result;
}
// 10009068: using guessed type int __cdecl UF_VEC3_angle_between(_DWORD, _DWORD, _DWORD, _DWORD);
// 1000906C: using guessed type int __cdecl UF_VEC3_copy(_DWORD, _DWORD);
// 10009070: using guessed type int __cdecl UF_VEC3_dot(_DWORD, _DWORD, _DWORD);
// 10009074: using guessed type int __cdecl UF_VEC3_sub(_DWORD, _DWORD, _DWORD);
// 1000908C: using guessed type int __cdecl UF_MTX3_vec_multiply_t(_DWORD, _DWORD, _DWORD);
// 10009090: using guessed type int __cdecl UF_VEC3_distance(_DWORD, _DWORD, _DWORD);
// 10009094: using guessed type int __cdecl UF_MTX3_z_vec(_DWORD, _DWORD);
// 10009098: using guessed type int __cdecl UF_VEC3_is_parallel(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100090B8: using guessed type int __cdecl UF_MTX3_x_vec(_DWORD, _DWORD);
// 100090BC: using guessed type int __cdecl UF_MTX3_y_vec(_DWORD, _DWORD);
// 100090C4: using guessed type int __cdecl UF_VEC3_cross(_DWORD, _DWORD, _DWORD);
// 100090C8: using guessed type int __cdecl UF_VEC3_unitize(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100090F8: using guessed type int __cdecl UF_VEC3_is_equal(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1000C010: using guessed type double dbl_1000C010;
// 1000C018: using guessed type char byte_1000C018;
// 1000C019: using guessed type char byte_1000C019;
// 1000C01A: using guessed type char byte_1000C01A;
// 1000C030: using guessed type double dbl_1000C030;
// 1000C0B0: using guessed type int dword_1000C0B0;
// 1000C0B4: using guessed type int dword_1000C0B4;
// 1000C0B8: using guessed type int dword_1000C0B8;
// 1000C0BC: using guessed type int dword_1000C0BC;
// 1000C0C0: using guessed type int dword_1000C0C0;
// 1000C0C4: using guessed type int dword_1000C0C4;
// 1000C0C8: using guessed type double dbl_1000C0C8;
// 1000C0D0: using guessed type double dbl_1000C0D0;
// 1000C0D8: using guessed type double dbl_1000C0D8;
// 1000C0E0: using guessed type double dbl_1000C0E0;
// 1000C0E8: using guessed type double dbl_1000C0E8;
// 1000C0F0: using guessed type double dbl_1000C0F0;
// 1000C0F8: using guessed type double dbl_1000C0F8;
// 1000C100: using guessed type double dbl_1000C100;
// 1000C108: using guessed type double dbl_1000C108;
// 1000C110: using guessed type double dbl_1000C110;
// 1000C118: using guessed type double dbl_1000C118;
// 1000C120: using guessed type double dbl_1000C120;
// 1000C130: using guessed type double dbl_1000C130;
// 1000C1C0: using guessed type int dword_1000C1C0;
// 1000C248: using guessed type double dbl_1000C248;
// 1000C250: using guessed type double dbl_1000C250;
// 1000C258: using guessed type double dbl_1000C258;
// 1000C260: using guessed type double dbl_1000C260;
// 1000C268: using guessed type double dbl_1000C268;
// 1000C270: using guessed type double dbl_1000C270;
// 1000C278: using guessed type double dbl_1000C278;
// 1000C280: using guessed type double dbl_1000C280;
// 1000C288: using guessed type double dbl_1000C288;
// 1000C290: using guessed type double dbl_1000C290;
// 1000C298: using guessed type double dbl_1000C298;
// 1000C2A0: using guessed type double dbl_1000C2A0;
// 1000C2A8: using guessed type double dbl_1000C2A8;
// 1000C2B0: using guessed type double dbl_1000C2B0;
// 1000C2B8: using guessed type double dbl_1000C2B8;
// 1000C2C0: using guessed type double dbl_1000C2C0;
// 1000C2C8: using guessed type int dword_1000C2C8;
// 1000C2CC: using guessed type int dword_1000C2CC;
// 1000C2D0: using guessed type int dword_1000C2D0;
// 1000C2D4: using guessed type int dword_1000C2D4;
// 1000C2D8: using guessed type int dword_1000C2D8;
// 1000C2DC: using guessed type int dword_1000C2DC;
// 1000C2E0: using guessed type int dword_1000C2E0;
// 1000C2E4: using guessed type int dword_1000C2E4;
// 1000C2E8: using guessed type int dword_1000C2E8;
// 1000C2EC: using guessed type int dword_1000C2EC;
// 1000C2F0: using guessed type int dword_1000C2F0;
// 1000C2F4: using guessed type int dword_1000C2F4;
// 1000C2F8: using guessed type int dword_1000C2F8;
// 1000C2FC: using guessed type int dword_1000C2FC;
// 1000C300: using guessed type int dword_1000C300;
// 1000C304: using guessed type int dword_1000C304;
// 1000C308: using guessed type int dword_1000C308;
// 1000C30C: using guessed type int dword_1000C30C;
// 1000C310: using guessed type int dword_1000C310;
// 1000C314: using guessed type int dword_1000C314;
// 1000C318: using guessed type int dword_1000C318;
// 1000C320: using guessed type double dbl_1000C320;
// 1000C328: using guessed type double dbl_1000C328;
// 1000C330: using guessed type int dword_1000C330;
// 1000C334: using guessed type int dword_1000C334;
// 1000C338: using guessed type int dword_1000C338;
// 1000C33C: using guessed type int dword_1000C33C;
// 1000C340: using guessed type int dword_1000C340;
// 1000C344: using guessed type int dword_1000C344;
// 1000C348: using guessed type double dbl_1000C348;
// 1000C350: using guessed type double dbl_1000C350;
// 1000C358: using guessed type double dbl_1000C358;
// 1000C360: using guessed type double dbl_1000C360;
// 1000C368: using guessed type double dbl_1000C368;
// 1000C370: using guessed type double dbl_1000C370;
// 1000C378: using guessed type char byte_1000C378;



//----------------------------------------------------------------------------------------

//----- (10002150) --------------------------------------------------------
int sub_10002150(int a1<eax>, int a2<ecx>, int a3)
{

  v4 = a1;
  v5 = a2;
  UF_MTX3_copy(a1 + 24, &v7);
  UF_MTX3_copy(v5 + 24, &v6);
  v12 = *(double *)v4;
  v15 = *(double *)v5;
  v13 = *(double *)(v4 + 8);
  v16 = *(double *)(v5 + 8);
  v14 = *(double *)(v4 + 16);
  v17 = *(double *)(v5 + 16);
  UF_MTX3_x_vec(&v7, &v10);
  UF_MTX3_y_vec(&v7, &v8);
  UF_MTX3_x_vec(&v6, &v11);
  UF_MTX3_y_vec(&v6, &v9);
  return UF_MTX4_csys_to_csys(&v12, &v10, &v8, &v15, &v11, &v9, a3);
}
// 100090B4: using guessed type int __cdecl UF_MTX3_copy(_DWORD, _DWORD);
// 100090B8: using guessed type int __cdecl UF_MTX3_x_vec(_DWORD, _DWORD);
// 100090BC: using guessed type int __cdecl UF_MTX3_y_vec(_DWORD, _DWORD);
// 100090C0: using guessed type int __cdecl UF_MTX4_csys_to_csys(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (10003080) --------------------------------------------------------
signed int __usercall sub_10003080<eax>(int a1<eax>, int a2)
{
  signed int result; // eax@1

  v21 = *(double *)a1;
  v3 = *(double *)(a1 + 32);
  v26 = &v17;
  v17 = v3;
  v9 = *(double *)(a1 + 64);
  v27 = &v9;
  v13 = *(double *)(a1 + 96);
  v22 = *(double *)(a1 + 8);
  v18 = *(double *)(a1 + 40);
  v10 = *(double *)(a1 + 72);
  v14 = *(double *)(a1 + 104);
  v23 = *(double *)(a1 + 16);
  v19 = *(double *)(a1 + 48);
  v11 = *(double *)(a1 + 80);
  v15 = *(double *)(a1 + 112);
  v24 = *(double *)(a1 + 24);
  v20 = *(double *)(a1 + 56);
  v12 = *(double *)(a1 + 88);
  v4 = *(double *)(a1 + 120);
  v25 = &v21;
  v16 = v4;
  v28 = &v13;
  result = sub_100029A0((int)&v25, 4, (int)&v7, (int)&v8);
  if ( !result )
  {
    v5 = 0;
    v6 = a2 + 64;
    do
    {
      *(_QWORD *)&v29 = 0i64;
      *(_QWORD *)&v30 = 0i64;
      *(_QWORD *)&v31 = 0i64;
      *(_QWORD *)&v32 = 0i64;
      *(&v29 + v5) = 1.0;
      result = sub_10002E60((int)&v7, (int)&v29, (int)&v25, 4, (int)&v7);
      *(_QWORD *)(v6 - 64) = *(_QWORD *)&v29;
      ++v5;
      *(_QWORD *)(v6 - 32) = *(_QWORD *)&v30;
      v6 += 8;
      *(_QWORD *)(v6 - 8) = *(_QWORD *)&v31;
      *(_QWORD *)(v6 + 24) = *(_QWORD *)&v32;
    }
    while ( v5 < 4 );
  }
  return result;
}

//----- (100029A0) --------------------------------------------------------
signed int __usercall sub_100029A0<eax>(int a1<esi>, signed int a2, int a3, int a4)
{

  v4 = a2;
  v5 = UF_allocate_memory(8 * a2, &v63);
  *(double *)a4 = 1.0;
  v69 = v5;
  v71 = 0;
  if ( a2 <= 0 )
  {
LABEL_20:
    v14 = 0;
    v70 = 0;
    if ( a2 > 0 )
    {
      v68 = a2 - 1;
      v15 = a1;
      v67 = a1;
      HIDWORD(v64) = a3 - a1;
      do
      {
        v16 = 0;
        v71 = 0;
        if ( v14 > 0 )
        {
          do
          {
            v17 = *(_DWORD *)(a1 + 4 * v16);
            v19 = *(double *)(v14 + v17);
            v18 = 0;
            if ( v16 >= 4 )
            {
              v66 = ((unsigned int)(v16 - 4) >> 2) + 1;
              v20 = v17 + 16;
              v21 = a1 + 8;
              v18 = 4 * v66;
              do
              {
                v22 = *(_DWORD *)(v21 - 4);
                v23 = *(double *)(*(_DWORD *)(v21 - 8) + v14) * *(double *)(v20 - 16);
                v20 += 32;
                v21 += 16;
                v24 = v66-- == 1;
                v19 = v19
                    - v23
                    - *(double *)(v22 + v14) * *(double *)(v20 - 40)
                    - *(double *)(*(_DWORD *)(v21 - 16) + v14) * *(double *)(v20 - 32)
                    - *(double *)(*(_DWORD *)(v21 - 12) + v14) * *(double *)(v20 - 24);
              }
              while ( !v24 );
              v15 = v67;
              v16 = v71;
            }
            if ( v18 < v16 )
            {
              v66 = *(_DWORD *)(a1 + 4 * v16) + 8 * v18;
              do
              {
                v25 = *(double *)(*(_DWORD *)(a1 + 4 * v18++) + v14) * *(double *)v66;
                v19 = v19 - v25;
                v66 += 8;
              }
              while ( v18 < v16 );
            }
            v26 = *(_DWORD *)(a1 + 4 * v16++);
            *(_QWORD *)(v14 + v26) = *(_QWORD *)&v19;
            v71 = v16;
          }
          while ( v16 < v70 );
          v4 = a2;
        }
        v27 = v70;
        v62 = 0.0;
        v28 = v70;
        v71 = v70;
        if ( v70 < v4 )
        {
          do
          {
            v29 = *(_DWORD *)(a1 + 4 * v28);
            v31 = *(double *)(v14 + v29);
            v30 = 0;
            if ( v14 >= 32 )
            {
              v66 = ((unsigned int)(v70 - 4) >> 2) + 1;
              v32 = v29 + 16;
              v33 = a1 + 8;
              v30 = 4 * v66;
              do
              {
                v34 = *(_DWORD *)(v33 - 4);
                v35 = *(double *)(*(_DWORD *)(v33 - 8) + v14) * *(double *)(v32 - 16);
                v32 += 32;
                v33 += 16;
                v36 = v66-- == 1;
                v31 = v31
                    - v35
                    - *(double *)(v34 + v14) * *(double *)(v32 - 40)
                    - *(double *)(*(_DWORD *)(v33 - 16) + v14) * *(double *)(v32 - 32)
                    - *(double *)(*(_DWORD *)(v33 - 12) + v14) * *(double *)(v32 - 24);
              }
              while ( !v36 );
              v15 = v67;
              v28 = v71;
            }
            if ( v30 < v70 )
            {
              v37 = *(_DWORD *)(a1 + 4 * v28) + 8 * v30;
              do
              {
                v38 = *(_DWORD *)(a1 + 4 * v30++);
                v39 = *(double *)(v38 + v14) * *(double *)v37;
                v37 += 8;
                v31 = v31 - v39;
              }
              while ( v30 < v70 );
              v28 = v71;
            }
            *(_QWORD *)(v14 + *(_DWORD *)(a1 + 4 * v28)) = *(_QWORD *)&v31;
            v40 = fabs(v31) * *(double *)(v69 + 8 * v28);
            if ( v40 >= v62 )
            {
              v62 = v40;
              v65 = v28;
            }
            ++v28;
            v71 = v28;
          }
          while ( v28 < a2 );
          v4 = a2;
          v27 = v70;
        }
        v42 = v65;
        if ( v27 != v65 )
        {
          v43 = 0;
          if ( v4 >= 4 )
          {
            do
            {
              v44 = *(_DWORD *)(a1 + 4 * v42);
              v45 = *(double *)(v44 + 8 * v43);
              v66 = v44 + 8 * v43;
              *(double *)(v44 + 8 * v43) = *(double *)(*(_DWORD *)v15 + 8 * v43);
              *(_QWORD *)(*(_DWORD *)v15 + 8 * v43) = *(_QWORD *)&v45;
              v46 = *(_DWORD *)(a1 + 4 * v42);
              v47 = *(double *)(v46 + 8 * v43 + 8);
              v66 = v46 + 8 * v43 + 8;
              *(double *)(v46 + 8 * v43 + 8) = *(double *)(*(_DWORD *)v15 + 8 * v43 + 8);
              *(_QWORD *)(*(_DWORD *)v15 + 8 * v43 + 8) = *(_QWORD *)&v47;
              v48 = *(_DWORD *)(a1 + 4 * v42);
              v49 = *(double *)(v48 + 8 * v43 + 16);
              v66 = v48 + 8 * v43 + 16;
              *(double *)(v48 + 8 * v43 + 16) = *(double *)(*(_DWORD *)v15 + 8 * v43 + 16);
              *(_QWORD *)(*(_DWORD *)v15 + 8 * v43 + 16) = *(_QWORD *)&v49;
              v50 = *(_DWORD *)(a1 + 4 * v42);
              v51 = *(double *)(v50 + 8 * v43 + 24);
              v66 = v50 + 8 * v43 + 24;
              *(double *)(v50 + 8 * v43 + 24) = *(double *)(*(_DWORD *)v15 + 8 * v43 + 24);
              v43 += 4;
              *(_QWORD *)(*(_DWORD *)v15 + 8 * v43 - 8) = *(_QWORD *)&v51;
            }
            while ( v43 < a2 - 3 );
            v4 = a2;
          }
          if ( v43 < v4 )
          {
            do
            {
              v52 = *(_DWORD *)(a1 + 4 * v42);
              v53 = *(double *)(v52 + 8 * v43);
              v66 = v52 + 8 * v43;
              *(double *)(v52 + 8 * v43) = *(double *)(*(_DWORD *)v15 + 8 * v43);
              ++v43;
              *(_QWORD *)(*(_DWORD *)v15 + 8 * v43 - 8) = *(_QWORD *)&v53;
              v4 = a2;
            }
            while ( v43 < a2 );
          }
          *(double *)a4 = -*(double *)a4;
          *(double *)(v69 + 8 * v42) = *(double *)(v14 + v69);
        }
        *(_DWORD *)(HIDWORD(v64) + v15) = v42;
        if ( *(double *)(*(_DWORD *)v15 + v14) == 0.0 )
          *(double *)(*(_DWORD *)v15 + v14) = 9.999999999999999e-21;
        if ( v70 != v4 - 1 )
        {
          v55 = 1.0 / *(double *)(*(_DWORD *)v15 + v14);
          v54 = v70 + 1;
          if ( v68 >= 4 )
          {
            v57 = ((unsigned int)(v4 - v54 - 4) >> 2) + 1;
            v56 = v15 + 12;
            v71 = v54 + 4 * v57;
            do
            {
              v58 = *(_DWORD *)(v56 - 8);
              v56 += 16;
              *(double *)(v14 + v58) = v55 * *(double *)(v58 + v14);
              *(double *)(v14 + *(_DWORD *)(v56 - 20)) = v55 * *(double *)(v14 + *(_DWORD *)(v56 - 20));
              *(double *)(v14 + *(_DWORD *)(v56 - 16)) = v55 * *(double *)(v14 + *(_DWORD *)(v56 - 16));
              --v57;
              *(double *)(v14 + *(_DWORD *)(v56 - 12)) = v55 * *(double *)(v14 + *(_DWORD *)(v56 - 12));
            }
            while ( v57 );
            v4 = a2;
            v54 = v71;
          }
          for ( ; v54 < v4; *(double *)(v14 + v59) = v55 * *(double *)(v59 + v14) )
            v59 = *(_DWORD *)(a1 + 4 * v54++);
        }
        --v68;
        v15 += 4;
        v14 += 8;
        v61 = __SETO__(v70 + 1, v4);
        v60 = v70++ + 1 - v4 < 0;
        v67 = v15;
      }
      while ( v60 ^ v61 );
    }
    UF_free(v69);
    result = 0;
  }
  else
  {
    while ( 1 )
    {
      v7 = 0.0;
      v6 = 0;
      if ( a2 >= 4 )
      {
        v8 = *(_DWORD *)(a1 + 4 * v71) + 16;
        v9 = ((unsigned int)(a2 - 4) >> 2) + 1;
        v6 = 4 * v9;
        do
        {
          v64 = fabs(*(double *)(v8 - 16));
          if ( v64 > v7 )
            v7 = v64;
          v64 = fabs(*(double *)(v8 - 8));
          if ( v64 > v7 )
            v7 = v64;
          v64 = fabs(*(double *)v8);
          if ( v64 > v7 )
            v7 = v64;
          v64 = fabs(*(double *)(v8 + 8));
          if ( v64 > v7 )
            v7 = v64;
          v8 += 32;
          --v9;
        }
        while ( v9 );
      }
      if ( v6 < a2 )
      {
        v10 = (long double *)(*(_DWORD *)(a1 + 4 * v71) + 8 * v6);
        v11 = a2 - v6;
        do
        {
          v64 = fabs(*v10);
          if ( v64 > v7 )
            v7 = v64;
          ++v10;
          --v11;
        }
        while ( v11 );
      }
      if ( v7 == 0.0 )
        break;
      v13 = __SETO__(v71 + 1, a2);
      v12 = (signed int)(v71++ + 1 - a2) < 0;
      *(double *)(v69 + 8 * v71 - 8) = 1.0 / v7;
      if ( !(v12 ^ v13) )
        goto LABEL_20;
    }
    UF_free(v69);
    result = 1;
  }
  return result;
}
// 10009078: using guessed type int __cdecl UF_free(_DWORD);
// 1000907C: using guessed type int __cdecl UF_allocate_memory(_DWORD, _DWORD);


//----- (10002E60) --------------------------------------------------------
int __fastcall sub_10002E60(int a1, int a2, int a3, int a4, int a5)
{
  int result; // eax@1


  result = a4;
  v6 = a3;
  v7 = 0;
  v41 = 0;
  if ( a4 > 0 )
  {
    v9 = v10;
    v8 = a5 - a3;
    v43 = a3;
    while ( 1 )
    {
      v12 = *(_DWORD *)(v6 + v8);
      v11 = *(double *)(a2 + 8 * v12);
      *(double *)(a2 + 8 * v12) = *(double *)(a2 + 8 * v7);
      if ( v41 )
      {
        v13 = v9;
        v47 = v9;
        if ( v7 - v9 >= 4 )
        {
          v16 = *(_DWORD *)v6 + 8 * v9 + 24;
          v45 = *(_DWORD *)v6 - a2;
          v15 = a2 + 8 * v9 + 8;
          v14 = ((unsigned int)(v7 - v9 - 4) >> 2) + 1;
          v47 = v9 + 4 * v14;
          do
          {
            v17 = *(double *)(v15 - 8);
            v15 += 32;
            v18 = v17 * *(double *)(v16 - 24);
            v16 += 32;
            --v14;
            v11 = v11
                - v18
                - *(double *)(v45 + v15 - 32) * *(double *)(v15 - 32)
                - *(double *)(v15 - 24) * *(double *)(v16 - 40)
                - *(double *)(v15 - 16) * *(double *)(v16 - 32);
          }
          while ( v14 );
          v6 = v43;
          v9 = v39;
          v13 = v47;
        }
        if ( v13 < v7 )
        {
          v21 = *(_DWORD *)v6 - a2;
          v20 = v7 - v47;
          v19 = a2 + 8 * v13;
          do
          {
            v22 = *(double *)(v19 + v21);
            v19 += 8;
            --v20;
            v11 = v11 - v22 * *(double *)(v19 - 8);
          }
          while ( v20 );
          v6 = v43;
        }
      }
      else
      {
        if ( v11 != 0.0 )
        {
          v9 = v7;
          v41 = 1;
          v39 = v7;
        }
      }
      result = a4;
      *(_QWORD *)(a2 + 8 * v7++) = *(_QWORD *)&v11;
      v6 += 4;
      v43 = v6;
      if ( v7 >= a4 )
        break;
      v8 = a5 - a3;
    }
  }
  v23 = result - 1;
  if ( result - 1 >= 0 )
  {
    result = result - v23 - 1;
    v25 = v23 + 1;
    v24 = a2 + 8 * v23;
    v26 = 32 - a2;
    v40 = v23 + 1;
    v42 = a2 + 8 * v23;
    v44 = result;
    while ( 1 )
    {
      v27 = *(double *)v24;
      v48 = v25;
      if ( result >= 4 )
      {
        v31 = *(_DWORD *)(a3 + 4 * v23);
        v32 = v26 + v24;
        v30 = v32 + v31;
        v46 = v31 - a2;
        v28 = ((unsigned int)(a4 - v25 - 4) >> 2) + 1;
        v48 = v25 + 4 * v28;
        v29 = v32 + a2 - 16;
        do
        {
          v33 = *(double *)(v29 - 8);
          v29 += 32;
          v34 = v33 * *(double *)(v30 - 24);
          v30 += 32;
          --v28;
          v27 = v27
              - v34
              - *(double *)(v46 + v29 - 32) * *(double *)(v29 - 32)
              - *(double *)(v29 - 24) * *(double *)(v30 - 40)
              - *(double *)(v29 - 16) * *(double *)(v30 - 32);
        }
        while ( v28 );
        v25 = v40;
        v24 = v42;
        result = v44;
      }
      if ( v48 < a4 )
      {
        v35 = a2 + 8 * v48;
        v36 = a4 - v48;
        do
        {
          v37 = *(double *)(*(_DWORD *)(a3 + 4 * v23) - a2 + v35);
          v35 += 8;
          --v36;
          v27 = v27 - v37 * *(double *)(v35 - 8);
        }
        while ( v36 );
        v24 = v42;
        result = v44;
      }
      v38 = v27 / *(double *)(*(_DWORD *)(a3 + 4 * v23) + 8 * v23);
      --v23;
      ++result;
      --v25;
      v24 -= 8;
      v44 = result;
      v40 = v25;
      v42 = v24;
      *(_QWORD *)(v24 + 8) = *(_QWORD *)&v38;
      if ( v23 < 0 )
        break;
      v26 = 32 - a2;
    }
  }
  return result;
}

//----- (100041E0) --------------------------------------------------------
int __cdecl sub_100041E0(int a1, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax@3

  UF_VEC3_sub(a1 + 24, a1, &v13);
  UF_VEC3_sub(a1, a2, &v9);
  UF_VEC3_sub(a2 + 24, a2, &v10);
  UF_VEC3_dot(&v13, &v9, &v16);
  UF_VEC3_dot(&v10, &v13, &v21);
  UF_VEC3_dot(&v10, &v9, &v17);
  UF_VEC3_dot(&v10, &v10, &v20);
  UF_VEC3_dot(&v13, &v13, &v19);
  if ( v20 == 0.0 )
  {
    UF_VEC3_copy(a2, a4);
    *(double *)a6 = 0.0;
    if ( v19 == 0.0 )
    {
      UF_VEC3_copy(a1, a3);
      *(double *)a5 = 0.0;
      return 0;
    }
    result = sub_100028E0(a4, a1, a3, a5);
    if ( result )
      return result;
    return 0;
  }
  if ( v19 == 0.0 )
  {
    UF_VEC3_copy(a1, a3);
    *(double *)a5 = 0.0;
    return 0;
  }
  v18 = v21 * v21 - v19 * v20;
  if ( v18 != 0.0 )
  {
    v7 = v21 * v21 / (v19 * v20);
    if ( v7 < 0.0 )
      v7 = -v7;
    if ( v7 < 1.0 - (dbl_1000C010 + dbl_1000C010) )
    {
      v8 = (v20 * v16 - v17 * v21) / v18;
      *(_QWORD *)a5 = *(_QWORD *)&v8;
      *(double *)a6 = (v8 * v21 + v17) / v20;
      *(double *)a3 = v13 * *(double *)a5 + *(double *)a1;
      *(double *)a4 = v10 * *(double *)a6 + *(double *)a2;
      *(double *)(a3 + 8) = v14 * *(double *)a5 + *(double *)(a1 + 8);
      *(double *)(a4 + 8) = v11 * *(double *)a6 + *(double *)(a2 + 8);
      result = 0;
      *(double *)(a3 + 16) = v15 * *(double *)a5 + *(double *)(a1 + 16);
      *(double *)(a4 + 16) = v12 * *(double *)a6 + *(double *)(a2 + 16);
      return result;
    }
  }
  UF_VEC3_copy(a1, a3);
  *(double *)a5 = 0.0;
  result = sub_100028E0(a3, a2, a4, a6);
  if ( !result )
    return 0;
  return result;
}
// 1000906C: using guessed type int __cdecl UF_VEC3_copy(_DWORD, _DWORD);
// 10009070: using guessed type int __cdecl UF_VEC3_dot(_DWORD, _DWORD, _DWORD);
// 10009074: using guessed type int __cdecl UF_VEC3_sub(_DWORD, _DWORD, _DWORD);
// 1000C010: using guessed type double dbl_1000C010;

//----- (100028E0) --------------------------------------------------------
int __cdecl sub_100028E0(int a1, int a2, int a3, int a4)
{
  int result; // eax@2

  UF_VEC3_sub(a2 + 24, a2, &v7);
  UF_VEC3_sub(a1, a2, &v6);
  v10 = v9 * v9 + v8 * v8 + v7 * v7;
  if ( v10 <= 0.0 )
  {
    *(double *)a4 = 0.0;
    UF_VEC3_copy(a2, a3);
    result = 0;
  }
  else
  {
    UF_VEC3_dot(&v7, &v6, &v11);
    v5 = v11 / v10;
    *(double *)a4 = v11 / v10;
    *(double *)a3 = v5 * v7 + *(double *)a2;
    *(double *)(a3 + 8) = v8 * *(double *)a4 + *(double *)(a2 + 8);
    result = 0;
    *(double *)(a3 + 16) = v9 * *(double *)a4 + *(double *)(a2 + 16);
  }
  return result;
}
// 1000906C: using guessed type int __cdecl UF_VEC3_copy(_DWORD, _DWORD);
// 10009070: using guessed type int __cdecl UF_VEC3_dot(_DWORD, _DWORD, _DWORD);
// 10009074: using guessed type int __cdecl UF_VEC3_sub(_DWORD, _DWORD, _DWORD);


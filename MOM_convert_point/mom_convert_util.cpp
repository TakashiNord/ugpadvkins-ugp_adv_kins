
//----- (10002860) --------------------------------------------------------
int __cdecl sub_10002860(int a1)
{
  int v2; // ecx@1
  int v3; // esi@1

  v2 = dword_1000C1C0;
  v3 = dword_1000C1C0 + 16;
  *(_DWORD *)(dword_1000C1C0 + 16) = *(_DWORD *)(a1 + 192);
  *(_DWORD *)(v3 + 4) = *(_DWORD *)(a1 + 196);
  *(_DWORD *)(v3 + 8) = *(_DWORD *)(a1 + 200);
  *(_DWORD *)(v3 + 12) = *(_DWORD *)(a1 + 204);
  *(_DWORD *)(v3 + 16) = *(_DWORD *)(a1 + 208);
  *(_DWORD *)(v3 + 20) = *(_DWORD *)(a1 + 212);
  *(_DWORD *)(v2 + 40) = *(_DWORD *)(a1 + 216);
  *(_DWORD *)(v2 + 44) = *(_DWORD *)(a1 + 220);
  *(_DWORD *)(v2 + 48) = *(_DWORD *)(a1 + 224);
  *(_DWORD *)(v2 + 52) = *(_DWORD *)(a1 + 228);
  *(_DWORD *)(v2 + 56) = *(_DWORD *)(a1 + 232);
  *(_DWORD *)(v2 + 60) = *(_DWORD *)(a1 + 236);
  *(double *)(v2 + 136) = *(double *)(a1 + 376);
  return 0;
}
// 1000C1C0: using guessed type int dword_1000C1C0;

//----- (10005470) --------------------------------------------------------
signed int __cdecl sub_10005470(const void *a1, int a2, int a3)
{
  const void *v3; // ebx@1
  signed int v4; // esi@3
  char v5; // zf@8
  char v7; // [sp+34h] [bp-98h]@1
  char v8[40]; // [sp+64h] [bp-68h]@1
  char v9[40]; // [sp+8Ch] [bp-40h]@1
  double v10; // [sp+B4h] [bp-18h]@2
  double v11; // [sp+BCh] [bp-10h]@2
  double v12; // [sp+C4h] [bp-8h]@2
  signed int v13; // [sp+D4h] [bp+8h]@1

  v3 = a1;
  memcpy(&v7, a1, 0x30u);
  UF_VEC3_add(&v7, dword_1000C1C0 + 16, &v7);
  UF_VEC3_sub(&v7, dword_1000C1C0 + 40, &v7);
  v13 = sub_10003400(&v7, (int)v9, (int)v8);
  UF_VEC3_add(v9, dword_1000C1C0 + 64, v9);
  UF_VEC3_add(v8, dword_1000C1C0 + 64, v8);
  if ( *(_BYTE *)(dword_1000C1C0 + 88) )
  {
    v10 = *((double *)v3 + 3);
    v11 = *((double *)v3 + 4);
    v12 = *((double *)v3 + 5);
    UF_VEC3_scale(
      dword_1000C1C0 + 96,
      &v10,
      &v10);
    UF_VEC3_add(v9, &v10, v9);
    UF_VEC3_add(v8, &v10, v8);
  }
  v4 = 0;
  do
  {
    *(double *)&v9[v4] = sub_10005760((int)&v9[v4], (long double *)(dword_1000C1C0 + 8));
    *(double *)&v8[v4] = sub_10005760((int)&v8[v4], (long double *)(dword_1000C1C0 + 8));
    v4 += 8;
  }
  while ( v4 <= 16 );
  if ( byte_1000C01A )
    byte_1000C01A = 0;
  else
    sub_100026F0((int)v9, (int)&unk_1000C3A8, (int)v8);
  v5 = byte_1000C378 == 0;
  memcpy((void *)a2, v9, 0x28u);
  memcpy((void *)a3, v8, 0x28u);
  memcpy(&unk_1000C3A8, (const void *)a2, 0x28u);
  memcpy(&unk_1000C380, (const void *)a3, 0x28u);
  if ( !v5 )
  {
    printf(
      "final ufunc mcoord[] = (%f,%f,%f), (%f,%f)\n",
      *(double *)a2,
      *(double *)(a2 + 8),
      *(double *)(a2 + 16),
      *(double *)(a2 + 24),
      *(double *)(a2 + 32));
    printf(
      "final ufunc alt_mcoord[] = (%f,%f,%f), (%f,%f)\n",
      *(double *)a3,
      *(double *)(a3 + 8),
      *(double *)(a3 + 16),
      *(double *)(a3 + 24),
      *(double *)(a3 + 32));
  }
  return v13;
}

////////////
//------------------------------------------------------------------------


//----- (10003400) --------------------------------------------------------
signed int __cdecl sub_10003400(const void *a1, int a2, int a3)
{
  v6 = byte_1000C378 == 0;
  v3 = a3;
  *(double *)a3 = 0.0;
  v5 = a1;
  v4 = a2;
  *(double *)a2 = 0.0;
  v89 = 0;
  v79 = 0;
  *(double *)(v3 + 8) = 0.0;
  *(double *)(a2 + 8) = 0.0;
  *(double *)(v3 + 16) = 0.0;
  *(double *)(a2 + 16) = 0.0;
  *(double *)(v3 + 24) = 0.0;
  *(double *)(a2 + 24) = 0.0;
  *(double *)(v3 + 32) = 0.0;
  *(double *)(a2 + 32) = 0.0;
  if ( !v6 )
  {
    printf("\n------------------------------------------------------\n");
    printf(
      "Starting old_pcoord_t[] = (%f,%f,%f,%f,%f,%f)\n",
      *(double *)a1,
      *((double *)a1 + 1),
      *((double *)a1 + 2),
      *((double *)a1 + 3),
      *((double *)a1 + 4),
      *((double *)a1 + 5));
  }
  if ( dword_1000C318 == 3 )
  {
    UF_MTX3_vec_multiply_t(a1, &unk_10009908, &v64);
    UF_MTX3_vec_multiply_t((char *)a1 + 24, &unk_10009908, &v70);
  }
  else
  {
    memcpy(&v64, a1, 0x30u);
    v4 = a2;
    v5 = a1;
  }
  UF_VEC3_is_zero(&v70, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &a3);
  if ( a3 )
    return 4;
  UF_VEC3_unitize(&v70, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v71, &v81);
  v78 = v81;
  v8 = *(_DWORD *)dword_1000C1C0;
  v74 = v82;
  v63 = v83;
  if ( v8 != 3 )
  {
    v80 = (dbl_1000C080 * v83
         + dbl_1000C060 * v82
         + dbl_1000C040 * v81
         - (dbl_1000C088 * v83 + dbl_1000C068 * v82 + dbl_1000C048 * v81) * dbl_1000C350)
        * dbl_1000C2C0;
    v20 = dbl_1000C070 * v83 + dbl_1000C050 * v82 + dbl_1000C030 * v81;
    v19 = dbl_1000C078 * v83 + dbl_1000C058 * v82 + dbl_1000C038 * v81;
    if ( fabs(dbl_1000C0F8) > dbl_1000C010 )
    {
      if ( v8 == 1 )
      {
        v22 = dbl_1000C0F0;
      }
      else
      {
        if ( v8 == 2 )
          v22 = dbl_1000C0F0;
        else
          v22 = v78;
      }
      v21 = (v22 - v80) / dbl_1000C0F8;
    }
    else
    {
      v21 = 0.0;
      v89 = 1;
    }
    v86 = v21;
    v75 = sqrt(v19 * v19 + v20 * v20);
    if ( fabs(v20) > dbl_1000C010 || fabs(v19) > dbl_1000C010 )
      v23 = atan2(v20, v19);
    else
      v23 = 0.0;
    if ( fabs(v75) > dbl_1000C010 )
      v24 = v86 / v75;
    else
      v24 = 0.0;
    v86 = v24;
    if ( dbl_1000C010 + 1.0 >= fabs(v24) )
    {
      v25 = 1.0 - v24 * v24;
      if ( fabs(v25) <= dbl_1000C010 )
        v25 = 0.0;
      if ( fabs(v24 - 1.0) > dbl_1000C010 )
        v26 = sqrt(v25);
      else
        v26 = 0.0;
      v87 = atan2(v26, v24) + v23;
      v88 = atan2(-v26, v24) + v23;
    }
    else
    {
      printf(
        "INPUT Point =%-.4f,%-.4f,%-.4f,%-.8f,%-.8f,%-.8f\n",
        *(double *)v5,
        *((double *)v5 + 1),
        *((double *)v5 + 2),
        *((double *)v5 + 3),
        *((double *)v5 + 4),
        *((double *)v5 + 5));
      printf("WARNING: Degenerated G_lambda(%f) out of range (-1, 1)\n", *(_QWORD *)&v86);
      v88 = 0.0;
      v89 = 1;
      v87 = 0.0;
    }
    v27 = 0;
    v28 = fabs(dbl_1000C2B8);
    do
    {
      v30 = sin(*(double *)((char *)&v87 + v27));
      v29 = cos(*(double *)((char *)&v87 + v27));
      if ( v28 > dbl_1000C010 )
      {
        v75 = -(v30 * dbl_1000C2C0);
        v80 = dbl_1000C2C0 * v29;
        v86 = -(dbl_1000C0F8 * dbl_1000C350);
        v31 = ((v30 * dbl_1000C078 + v29 * dbl_1000C070 - dbl_1000C348 * dbl_1000C088) * v63
             + (v30 * dbl_1000C058 + v29 * dbl_1000C050 - dbl_1000C348 * dbl_1000C068) * v74
             + (v30 * dbl_1000C038 + v29 * dbl_1000C030 - dbl_1000C348 * dbl_1000C048) * v78)
            / dbl_1000C2B8;
        v86 = ((dbl_1000C0F8 * dbl_1000C080 + v80 * dbl_1000C078 + v75 * dbl_1000C070 + v86 * dbl_1000C088) * v63
             + (dbl_1000C0F8 * dbl_1000C060 + v80 * dbl_1000C058 + v75 * dbl_1000C050 + v86 * dbl_1000C068) * v74
             + (dbl_1000C0F8 * dbl_1000C040 + v80 * dbl_1000C038 + v75 * dbl_1000C030 + v86 * dbl_1000C048) * v78)
            * -1.0
            / dbl_1000C2B8;
      }
      else
      {
        v86 = 0.0;
        v31 = 0.0;
      }
      if ( fabs(v31) > dbl_1000C010 || fabs(v86) > dbl_1000C010 )
      {
        v32 = atan2(v86, v31);
      }
      else
      {
        v89 = 1;
        v32 = 0.0;
      }
      *(_QWORD *)((char *)&v84 + v27) = *(_QWORD *)&v32;
      v27 += 8;
    }
    while ( v27 < 16 );
    goto LABEL_62;
  }
  if ( dword_1000C318 )
  {
    if ( dword_1000C318 != 1 && dword_1000C318 != 3 )
      return 2;
    if ( fabs(dbl_1000C0E8 - 1.0) > dbl_1000C010
      && (v11 = (v83 - dbl_1000C0E8 * dbl_1000C0E8) / (1.0 - dbl_1000C0E8 * dbl_1000C0E8),
          dbl_1000C010 + 1.0 >= fabs(v11)) )
    {
      sub_10001FE0(v11);
      v87 = v11;
      v12 = -v11;
    }
    else
    {
      v89 = 1;
      v87 = dbl_1000C248;
      v12 = dbl_1000C250;
    }
    v88 = v12;
    v13 = 0;
    do
    {
      v15 = sin(*(double *)((char *)&v87 + v13));
      v16 = (1.0 - cos(*(double *)((char *)&v87 + v13))) * dbl_1000C0E8;
      v86 = dbl_1000C0D8 * v16 + dbl_1000C0E0 * v15;
      v17 = v16 * dbl_1000C0E0 - dbl_1000C0D8 * v15;
      v80 = v82 * v17 + v86 * v81;
      v14 = v86 * v82 - v17 * v81;
      if ( fabs(v14) > dbl_1000C010 || fabs(v80) > dbl_1000C010 )
      {
        v18 = atan2(v80, v14);
      }
      else
      {
        v89 = 1;
        v18 = *(double *)((char *)&dbl_1000C100 + v13);
      }
      *(_QWORD *)((char *)&v84 + v13) = *(_QWORD *)&v18;
      v13 += 8;
    }
    while ( v13 < 16 );
LABEL_62:
    if ( !v89 )
      goto LABEL_66;
    goto LABEL_63;
  }
  v87 = asin(-v82);
  v9 = sqrt(v83 * v83 + v81 * v81);
  v86 = v9;
  sub_10001FE0(v9);
  v88 = v9;
  if ( fabs(v87 - v9) <= dbl_1000C010 )
  {
    v10 = -v86;
    sub_10001FE0(-v86);
    v88 = v10;
  }
  if ( fabs(v81) > dbl_1000C010 || fabs(v83) > dbl_1000C010 )
  {
    v84 = atan2(v83, v81);
    v85 = atan2(-v83, -v81);
    goto LABEL_66;
  }
  v89 = 1;
  v84 = dbl_1000C100;
  v85 = dbl_1000C108;
LABEL_63:
  if ( *(_DWORD *)dword_1000C1C0 != 3 )
  {
    v87 = dbl_1000C248;
    v88 = dbl_1000C250;
    v84 = dbl_1000C100;
    v85 = dbl_1000C108;
  }
  v79 = 1;
LABEL_66:
  if ( byte_1000C019 && (*(_DWORD *)dword_1000C1C0 == 2 || *(_DWORD *)dword_1000C1C0 == 3) )
  {
    sub_10002510((int)&v84, (int)&v87);
    result = v79;
    dbl_1000C320 = v87;
    dbl_1000C328 = v88;
    dbl_1000C0C8 = v84;
    dbl_1000C0D0 = v85;
    return result;
  }
  v33 = *(_DWORD *)dword_1000C1C0;
  if ( *(_DWORD *)dword_1000C1C0 == 1 )
  {
    v34 = v64;
    v35 = v65;
    v36 = v66;
    *(_DWORD *)v4 = v64;
    *(_DWORD *)(v4 + 4) = v35;
    *(_DWORD *)(v4 + 8) = v36;
    *(_DWORD *)(v4 + 12) = v67;
    *(_DWORD *)(v4 + 16) = v68;
    v37 = v69;
    *(_DWORD *)(v4 + 20) = v69;
    *(_DWORD *)v3 = v34;
    v38 = v66;
    *(_DWORD *)(v3 + 4) = v35;
    v39 = v67;
    *(_DWORD *)(v3 + 8) = v38;
    v40 = v68;
    *(_DWORD *)(v3 + 12) = v39;
    *(_DWORD *)(v3 + 16) = v40;
    *(_DWORD *)(v3 + 20) = v37;
  }
  else
  {
    if ( v33 == 2 || v33 == 3 )
    {
      if ( byte_1000C378 )
      {
        ((void (__cdecl *)(_DWORD))printf)("About adjusting theta with initial angle...\n");
        printf(
          "computing t1[0]=%f, t2[0]=%f, (Init_T1[0]*2-t1[0])=%f,(Init_T2[0]*2-t2[0])=%f\n",
          v87 * 57.29577951308235,
          v84 * 57.29577951308235,
          (dbl_1000C320 + dbl_1000C320 - v87) * 57.29577951308235,
          (dbl_1000C0C8 + dbl_1000C0C8 - v84) * 57.29577951308235);
        printf(
          "computing t1[1]=%f, t2[1]=%f, (Init_T1[1]*2-t1[1])=%f,(Init_T2[1]*2-t2[1])=%f\n",
          v88 * 57.29577951308235,
          v85 * 57.29577951308235,
          (dbl_1000C328 + dbl_1000C328 - v88) * 57.29577951308235,
          (dbl_1000C0D0 + dbl_1000C0D0 - v85) * 57.29577951308235);
      }
      sub_10002510((int)&v84, (int)&v87);
      if ( *(_DWORD *)dword_1000C1C0 == 2 )
      {
        v73 = v87;
        v74 = v88;
        v77 = v84;
        v78 = v85;
        sub_100031B0((int)&v77, (int)&v81, (int)&v73);
        v87 = v73;
        v88 = v74;
        v84 = v77;
        v85 = v78;
        sub_10002220((int)&v64, v4, v73, v77, 1);
        sub_10002220((int)&v64, v3, v74, v78, 1);
      }
      else
      {
        sub_10002030((int)&dbl_1000C110, (int)&v62, -v84);
        sub_10005BC0(v41);
        UF_MTX4_vec3_multiply_t(&v64, &v62, v4);
        sub_10002030((int)&dbl_1000C110, (int)&v62, -v85);
        sub_10005BC0(v42);
        UF_MTX4_vec3_multiply_t(&v64, &v62, v3);
        if ( dword_1000C318 == 3 )
        {
          v43 = 0;
          do
          {
            v44 = v4;
            if ( v43 )
              v44 = v3;
            UF_MTX3_vec_multiply_t(v44, &unk_100098C0, v44);
            ++v43;
          }
          while ( v43 < 2 );
        }
      }
    }
  }
  v46 = dword_1000C1C0;
  v45 = *(_DWORD *)dword_1000C1C0;
  if ( *(_DWORD *)dword_1000C1C0 == 1 )
  {
    v78 = *(double *)(dword_1000C1C0 + 144) + *(double *)(dword_1000C1C0 + 136);
    UF_VEC3_affine_comb(v4, LODWORD(v78), HIDWORD(v78), &v81, v4);
    UF_VEC3_affine_comb(v3, LODWORD(v78), HIDWORD(v78), &v81, v3);
    sub_100023B0(v4, v87, v4);
    sub_100023B0(v3, v88, v3);
LABEL_90:
    v46 = dword_1000C1C0;
    goto LABEL_91;
  }
  if ( v45 == 3 )
  {
    sub_10002030((int)&dbl_1000C110, (int)&v61, -v84);
    sub_10005BC0(v49);
    UF_MTX4_vec3_multiply_t(&v81, &v61, &v76);
    UF_VEC3_unitize(&v76, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v71, &v76);
    v47 = UF_VEC3_affine_comb;
    UF_VEC3_affine_comb(
      v4,
      COERCE_UNSIGNED_INT64(*(double *)(dword_1000C1C0 + 136)),
      COERCE_UNSIGNED_INT64(*(double *)(dword_1000C1C0 + 136)) >> 32,
      &v76,
      v4);
    *(double *)&v48 = *(double *)(dword_1000C1C0 + 136);
    v60 = v3;
    v59[0] = &v76;
LABEL_89:
    v47(v3, v48, v48 >> 32, v59[0], v60);
    goto LABEL_90;
  }
  if ( v45 == 2 )
  {
    sub_10002220((int)&v81, (int)&v76, v87, v84, 0);
    sub_10002220((int)&v81, (int)&v72, v88, v85, 0);
    UF_VEC3_unitize(&v76, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v71, &v76);
    UF_VEC3_unitize(&v72, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v71, &v72);
    v47 = UF_VEC3_affine_comb;
    UF_VEC3_affine_comb(
      v4,
      COERCE_UNSIGNED_INT64(*(double *)(dword_1000C1C0 + 136)),
      COERCE_UNSIGNED_INT64(*(double *)(dword_1000C1C0 + 136)) >> 32,
      &v76,
      v4);
    *(double *)&v48 = *(double *)(dword_1000C1C0 + 136);
    v60 = v3;
    v59[0] = &v72;
    goto LABEL_89;
  }
LABEL_91:
  v50 = byte_1000C018 == 0;
  *(double *)(v4 + 24) = v87 * 57.29577951308235;
  *(double *)(v3 + 24) = v88 * 57.29577951308235;
  *(double *)(v4 + 32) = v84 * 57.29577951308235;
  *(double *)(v3 + 32) = v85 * 57.29577951308235;
  if ( !v50 )
  {
    if ( *(_DWORD *)v46 != 3 )
    {
      v51 = *(double *)(v4 + 32) - 90.0;
      UNDEF(v52);
      *(_QWORD *)(v4 + 32) = *(_QWORD *)&v51;
      if ( v53 | v54 )
        *(double *)(v4 + 32) = v51 + 360.0;
      v55 = *(double *)(v3 + 32) - 90.0;
      UNDEF(v56);
      *(_QWORD *)(v3 + 32) = *(_QWORD *)&v55;
      if ( v57 | v58 )
        *(double *)(v3 + 32) = v55 + 360.0;
    }
  }
  if ( v89 )
  {
    if ( *(_DWORD *)v46 != 3 )
    {
      *(_DWORD *)(v4 + 24) = dword_1000C2E0;
      *(_DWORD *)(v4 + 28) = dword_1000C2E4;
      *(_DWORD *)(v4 + 32) = dword_1000C2E8;
      *(_DWORD *)(v4 + 36) = dword_1000C2EC;
      *(_DWORD *)(v3 + 24) = dword_1000C308;
      *(_DWORD *)(v3 + 28) = dword_1000C30C;
      *(_DWORD *)(v3 + 32) = dword_1000C310;
      *(_DWORD *)(v3 + 36) = dword_1000C314;
    }
  }
  if ( byte_1000C378 )
  {
    if ( fabs(v87 - v88) <= dbl_1000C010 )
    {
      if ( fabs(v84 - v85) <= dbl_1000C010 )
        printf("WARNING: same value of rotary produced:\n");
    }
  }
  result = v79;
  memcpy(&dword_1000C2C8, (const void *)a2, 0x28u);
  memcpy(&dword_1000C2F0, (const void *)v3, 0x28u);
  dbl_1000C248 = v87;
  dbl_1000C250 = v88;
  dbl_1000C100 = v84;
  dbl_1000C108 = v85;
  return result;
}
// 10009064: using guessed type int __cdecl UF_MTX4_vec3_multiply_t(_DWORD, _DWORD, _DWORD);
// 10009084: using guessed type int __cdecl UF_VEC3_affine_comb(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10009088: using guessed type int __cdecl UF_VEC3_is_zero(_DWORD, _DWORD, _DWORD, _DWORD);
// 1000908C: using guessed type int __cdecl UF_MTX3_vec_multiply_t(_DWORD, _DWORD, _DWORD);
// 100090C8: using guessed type int __cdecl UF_VEC3_unitize(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1000C010: using guessed type double dbl_1000C010;
// 1000C018: using guessed type char byte_1000C018;
// 1000C019: using guessed type char byte_1000C019;
// 1000C030: using guessed type double dbl_1000C030;
// 1000C038: using guessed type double dbl_1000C038;
// 1000C040: using guessed type double dbl_1000C040;
// 1000C048: using guessed type double dbl_1000C048;
// 1000C050: using guessed type double dbl_1000C050;
// 1000C058: using guessed type double dbl_1000C058;
// 1000C060: using guessed type double dbl_1000C060;
// 1000C068: using guessed type double dbl_1000C068;
// 1000C070: using guessed type double dbl_1000C070;
// 1000C078: using guessed type double dbl_1000C078;
// 1000C080: using guessed type double dbl_1000C080;
// 1000C088: using guessed type double dbl_1000C088;
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
// 1000C1C0: using guessed type int dword_1000C1C0;
// 1000C248: using guessed type double dbl_1000C248;
// 1000C250: using guessed type double dbl_1000C250;
// 1000C2B8: using guessed type double dbl_1000C2B8;
// 1000C2C0: using guessed type double dbl_1000C2C0;
// 1000C2C8: using guessed type int dword_1000C2C8;
// 1000C2E0: using guessed type int dword_1000C2E0;
// 1000C2E4: using guessed type int dword_1000C2E4;
// 1000C2E8: using guessed type int dword_1000C2E8;
// 1000C2EC: using guessed type int dword_1000C2EC;
// 1000C2F0: using guessed type int dword_1000C2F0;
// 1000C308: using guessed type int dword_1000C308;
// 1000C30C: using guessed type int dword_1000C30C;
// 1000C310: using guessed type int dword_1000C310;
// 1000C314: using guessed type int dword_1000C314;
// 1000C318: using guessed type int dword_1000C318;
// 1000C320: using guessed type double dbl_1000C320;
// 1000C328: using guessed type double dbl_1000C328;
// 1000C348: using guessed type double dbl_1000C348;
// 1000C350: using guessed type double dbl_1000C350;
// 1000C378: using guessed type char byte_1000C378;



//----- (10005760) --------------------------------------------------------
double __cdecl sub_10005760(int a1, long double *a2)
{
  double result; // st7@2
  double v3; // st7@3
  double v4; // st7@3
  double v5; // [sp+8h] [bp-8h]@3

  if ( fabs(fabs(*a2)) > 1.0e-10 )
  {
    v4 = 1.0 / *a2;
    v5 = v4;
    v3 = v4 * *(double *)a1;
    if ( v3 >= 0.000001 )
    {
      result = floor(v3 + 0.5) / v5;
    }
    else
    {
      if ( v3 <= -0.000001 )
        result = ceil(v3 - 0.5) / v5;
      else
        result = 0.0 / v5;
    }
  }
  else
  {
    result = 0.0;
  }
  return result;
}

//----- (100026F0) --------------------------------------------------------
void __usercall sub_100026F0(int a1<edx>, int a2<ecx>, int a3<ebx>)
{
  double v3; // st7@1
  double v4; // st7@7
  char v5; // [sp+0h] [bp-28h]@14

  v3 = *(double *)(a1 + 24);
  if ( v3 <= 0.0 )
  {
    if ( v3 < 0.0 )
      v3 = v3 + 360.0;
  }
  else
  {
    v3 = v3 - 360.0;
  }
  if ( fabs(*(double *)(a2 + 24) - v3) < fabs(*(double *)(a2 + 24) - *(double *)(a1 + 24)) )
    *(_QWORD *)(a1 + 24) = *(_QWORD *)&v3;
  v4 = *(double *)(a1 + 32);
  if ( v4 <= 0.0 )
  {
    if ( v4 < 0.0 )
      v4 = v4 + 360.0;
  }
  else
  {
    v4 = v4 - 360.0;
  }
  if ( fabs(*(double *)(a2 + 32) - v4) < fabs(*(double *)(a2 + 32) - *(double *)(a1 + 32)) )
    *(_QWORD *)(a1 + 32) = *(_QWORD *)&v4;
  if ( fabs(*(double *)(a2 + 24) - *(double *)(a3 + 24)) < fabs(*(double *)(a2 + 24) - *(double *)(a1 + 24)) )
  {
    memcpy(&v5, (const void *)a1, 0x28u);
    memcpy((void *)a1, (const void *)a3, 0x28u);
    memcpy((void *)a3, &v5, 0x28u);
  }
  if ( *(double *)(dword_1000C1C0 + 104) - dbl_1000C010 >= *(double *)(a1 + 24)
    || dbl_1000C010 + *(double *)(dword_1000C1C0 + 112) <= *(double *)(a1 + 24) )
  {
    if ( *(double *)(dword_1000C1C0 + 120) - dbl_1000C010 < *(double *)(a3 + 24) )
    {
      if ( dbl_1000C010 + *(double *)(dword_1000C1C0 + 128) > *(double *)(a3 + 24) )
      {
        memcpy(&v5, (const void *)a1, 0x28u);
        memcpy((void *)a1, (const void *)a3, 0x28u);
        memcpy((void *)a3, &v5, 0x28u);
      }
    }
  }
}
// 1000C010: using guessed type double dbl_1000C010;
// 1000C1C0: using guessed type int dword_1000C1C0;

//----- (10002030) --------------------------------------------------------
int __usercall sub_10002030<eax>(int result<eax>, int a2<ecx>, long double a3)
{
  long double v3; // st7@1
  long double v4; // st6@1
  double v5; // ST08_8@1
  double v6; // ST00_8@1

  v3 = cos(a3);
  v4 = sin(a3);
  v5 = *(double *)(result + 8) * *(double *)(result + 8);
  v6 = *(double *)(result + 16) * *(double *)(result + 16);
  *(long double *)a2 = (1.0 - *(double *)result * *(double *)result) * v3 + *(double *)result * *(double *)result;
  *(long double *)(a2 + 8) = *(double *)(result + 8) * *(double *)result * (1.0 - v3) + v4 * *(double *)(result + 16);
  *(long double *)(a2 + 16) = *(double *)(result + 16) * *(double *)result * (1.0 - v3) - v4 * *(double *)(result + 8);
  *(double *)(a2 + 24) = 0.0;
  *(long double *)(a2 + 32) = *(double *)(result + 8) * *(double *)result * (1.0 - v3) - v4 * *(double *)(result + 16);
  *(long double *)(a2 + 40) = (1.0 - v5) * v3 + v5;
  *(long double *)(a2 + 48) = *(double *)(result + 16) * *(double *)(result + 8) * (1.0 - v3) + v4 * *(double *)result;
  *(double *)(a2 + 56) = 0.0;
  *(long double *)(a2 + 64) = *(double *)(result + 16) * *(double *)result * (1.0 - v3) + v4 * *(double *)(result + 8);
  *(long double *)(a2 + 72) = *(double *)(result + 16) * *(double *)(result + 8) * (1.0 - v3) - v4 * *(double *)result;
  *(long double *)(a2 + 80) = (1.0 - v6) * v3 + v6;
  *(double *)(a2 + 88) = 0.0;
  *(double *)(a2 + 96) = 0.0;
  *(double *)(a2 + 104) = 0.0;
  *(double *)(a2 + 112) = 0.0;
  *(double *)(a2 + 120) = 1.0;
  return result;
}



//----- (10002220) --------------------------------------------------------
int __usercall sub_10002220<eax>(int a1<eax>, int a2<esi>, double a3, double a4, signed int a5)
{
  int result; // eax@1

  v6 = *(_DWORD *)(a1 + 4);
  v31 = *(_DWORD *)a1;
  v7 = *(_DWORD *)(a1 + 8);
  v37 = (double)a5;
  v32 = v6;
  v8 = *(_DWORD *)(a1 + 12);
  v33 = v7;
  v9 = *(_DWORD *)(a1 + 16);
  v34 = v8;
  v10 = *(_DWORD *)(a1 + 20);
  v30 = *(double *)(dword_1000C1C0 + 8);
  v35 = v9;
  v20 = 0.0;
  v21 = 0.0;
  v36 = v10;
  v22 = 0.0;
  UF_MTX4_rotation(
    &dword_1000C0B0,
    &dbl_1000C110,
    COERCE_UNSIGNED_INT64(a4 * -57.29577951308235),
    COERCE_UNSIGNED_INT64(a4 * -57.29577951308235) >> 32,
    &v18);
  sub_10005BC0((int)&v18);
  UF_MTX4_ask_rotation(&v18, &v17);
  UF_MTX3_vec_multiply(&dbl_1000C0D8, &v17, &v23);
  UF_VEC3_unitize(&v23, LODWORD(v30), HIDWORD(v30), &a4, &v23);
  UF_MTX4_vec3_multiply(&v20, &v18, &v19);
  UF_MTX4_rotation(
    &v19,
    &v23,
    COERCE_UNSIGNED_INT64(a3 * -57.29577951308235),
    COERCE_UNSIGNED_INT64(a3 * -57.29577951308235) >> 32,
    &v16);
  sub_10005BC0((int)&v16);
  UF_MTX4_multiply(&v18, &v16, &v15);
  sub_10005BC0((int)&v15);
  UF_MTX4_vec_multiply(&v31, &v15, &v24);
  v11 = v25;
  v12 = v26;
  *(_DWORD *)a2 = v24;
  result = v27;
  *(_DWORD *)(a2 + 4) = v11;
  v13 = v28;
  *(_DWORD *)(a2 + 8) = v12;
  v14 = v29;
  *(_DWORD *)(a2 + 12) = result;
  *(_DWORD *)(a2 + 16) = v13;
  *(_DWORD *)(a2 + 20) = v14;
  return result;
}
// 10009054: using guessed type int __cdecl UF_MTX3_vec_multiply(_DWORD, _DWORD, _DWORD);
// 10009058: using guessed type int __cdecl UF_MTX4_ask_rotation(_DWORD, _DWORD);
// 1000905C: using guessed type int __cdecl UF_MTX4_rotation(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10009080: using guessed type int __cdecl UF_MTX4_vec3_multiply(_DWORD, _DWORD, _DWORD);
// 100090AC: using guessed type int __cdecl UF_MTX4_multiply(_DWORD, _DWORD, _DWORD);
// 100090B0: using guessed type int __cdecl UF_MTX4_vec_multiply(_DWORD, _DWORD, _DWORD);
// 100090C8: using guessed type int __cdecl UF_VEC3_unitize(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1000C0B0: using guessed type int dword_1000C0B0;
// 1000C0D8: using guessed type double dbl_1000C0D8;
// 1000C110: using guessed type double dbl_1000C110;
// 1000C1C0: using guessed type int dword_1000C1C0;

//----- (100023B0) --------------------------------------------------------
int __cdecl sub_100023B0(int a1, double a2, int a3)
{
  char v4; // [sp+Ch] [bp-E0h]@1
  char v5; // [sp+8Ch] [bp-60h]@1
  char v6; // [sp+D4h] [bp-18h]@1

  UF_MTX4_rotation(
    &dword_1000C330,
    &dbl_1000C0D8,
    COERCE_UNSIGNED_INT64(a2 * 57.29577951308235),
    COERCE_UNSIGNED_INT64(a2 * 57.29577951308235) >> 32,
    &v4);
  sub_10005BC0((int)&v4);
  UF_MTX4_ask_rotation(&v4, &v5);
  UF_MTX3_vec_multiply(&dword_1000C0B0, &v5, &v6);
  return UF_VEC3_add(a1, &v6, a3);
}
// 10009054: using guessed type int __cdecl UF_MTX3_vec_multiply(_DWORD, _DWORD, _DWORD);
// 10009058: using guessed type int __cdecl UF_MTX4_ask_rotation(_DWORD, _DWORD);
// 1000905C: using guessed type int __cdecl UF_MTX4_rotation(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10009060: using guessed type int __cdecl UF_VEC3_add(_DWORD, _DWORD, _DWORD);
// 1000C0B0: using guessed type int dword_1000C0B0;
// 1000C0D8: using guessed type double dbl_1000C0D8;
// 1000C330: using guessed type int dword_1000C330;

//----- (10002510) --------------------------------------------------------
void __fastcall sub_10002510(int a1, int a2)
{
  double v2; // st7@5
  double v3; // st7@8
  __int16 v4; // fps@8
  unsigned __int8 v5; // c0@8
  unsigned __int8 v6; // c3@8
  double v7; // st7@11
  double v8; // [sp+0h] [bp-8h]@4

  if ( fabs(*(double *)a2 - *(double *)(a2 + 8)) <= dbl_1000C010 )
  {
    if ( fabs(*(double *)a1 - *(double *)(a1 + 8)) <= dbl_1000C010 )
    {
      if ( fabs(*(double *)a2 - *(double *)a1) > dbl_1000C010 )
      {
        v8 = -dbl_1000C010;
        if ( *(double *)a2 >= v8 )
        {
          if ( *(double *)a1 >= v8 )
          {
            if ( *(double *)(a1 + 8) > dbl_1000C010 )
              *(double *)(a1 + 8) = *(double *)(a1 + 8) - 6.283185307179586;
          }
          else
          {
            v7 = *(double *)a1 + 6.283185307179586;
            if ( fabs(v7 - *(double *)a2) <= dbl_1000C010 )
            {
              if ( *(double *)(a1 + 8) < v8 )
                *(double *)(a1 + 8) = *(double *)(a1 + 8) + 6.283185307179586;
            }
            else
            {
              *(_QWORD *)a1 = *(_QWORD *)&v7;
              if ( fabs(v7 - *(double *)(a1 + 8)) <= dbl_1000C010 )
                *(double *)(a1 + 8) = 6.283185307179586 - v7;
            }
          }
        }
        else
        {
          v2 = *(double *)a2 + 6.283185307179586;
          *(_QWORD *)a2 = *(_QWORD *)&v2;
          *(double *)(a2 + 8) = 6.283185307179586 - v2;
        }
      }
    }
  }
  if ( fabs(*(double *)a2 - *(double *)a1) <= dbl_1000C010 )
  {
    if ( fabs(*(double *)(a2 + 8) - *(double *)(a1 + 8)) <= dbl_1000C010 )
    {
      v3 = *(double *)(a1 + 8);
      UNDEF(v4);
      if ( v5 | v6 )
      {
        if ( v3 <= dbl_1000C010 )
        {
          if ( fabs(*(double *)a2) <= dbl_1000C010 )
          {
            if ( fabs(*(double *)a1) <= dbl_1000C010 )
              *(double *)(a1 + 8) = 6.283185307179586;
          }
        }
        else
        {
          *(double *)(a1 + 8) = 6.283185307179586 - *(double *)(a1 + 8);
        }
      }
      else
      {
        *(double *)(a1 + 8) = v3 + 6.283185307179586;
      }
    }
  }
}
// 1000C010: using guessed type double dbl_1000C010;

//----- (10005BC0) --------------------------------------------------------
signed int __cdecl sub_10005BC0(int a1)
{
  signed int v2; // edi@1
  char v3; // [sp+8h] [bp-48h]@1

  UF_MTX4_ask_rotation(a1, &v3);
  v2 = sub_10005800((int)&v3);
  UF_MTX4_edit_rotation(a1, &v3);
  return v2;
}
// 10009058: using guessed type int __cdecl UF_MTX4_ask_rotation(_DWORD, _DWORD);
// 100090A0: using guessed type int __cdecl UF_MTX4_edit_rotation(_DWORD, _DWORD);

//----- (10005800) --------------------------------------------------------
signed int __usercall sub_10005800<eax>(int a1<eax>)
{

  v2 = a1;
  UF_VEC3_copy(a1, &v25);
  v1 = (long double *)(v2 + 24);
  UF_VEC3_copy(v2 + 24, &v24);
  UF_VEC3_copy(v2 + 48, &v23);
  UF_MTX3_copy(v2, &v22);
  v3 = fabs(*(double *)v2);
  if ( v3 > 1.0e-10 )
  {
    if ( fabs(v3 - 1.0) > 1.0e-10 )
      goto LABEL_8;
    if ( *(double *)v2 <= 0.0 )
      v4 = -1.0;
    else
      v4 = 1.0;
  }
  else
  {
    v4 = 0.0;
  }
  *(_QWORD *)v2 = *(_QWORD *)&v4;
LABEL_8:
  v5 = fabs(*(double *)(v2 + 8));
  if ( v5 > 1.0e-10 )
  {
    if ( fabs(v5 - 1.0) > 1.0e-10 )
      goto LABEL_15;
    if ( *(double *)(v2 + 8) <= 0.0 )
      v6 = -1.0;
    else
      v6 = 1.0;
  }
  else
  {
    v6 = 0.0;
  }
  *(_QWORD *)(v2 + 8) = *(_QWORD *)&v6;
LABEL_15:
  v7 = fabs(*(double *)(v2 + 16));
  if ( v7 > 1.0e-10 )
  {
    if ( fabs(v7 - 1.0) > 1.0e-10 )
      goto LABEL_22;
    if ( *(double *)(v2 + 16) <= 0.0 )
      v8 = -1.0;
    else
      v8 = 1.0;
  }
  else
  {
    v8 = 0.0;
  }
  *(_QWORD *)(v2 + 16) = *(_QWORD *)&v8;
LABEL_22:
  v9 = fabs(*v1);
  if ( v9 > 1.0e-10 )
  {
    if ( fabs(v9 - 1.0) > 1.0e-10 )
      goto LABEL_29;
    if ( *v1 <= 0.0 )
      v10 = -1.0;
    else
      v10 = 1.0;
  }
  else
  {
    v10 = 0.0;
  }
  *(_QWORD *)v1 = *(_QWORD *)&v10;
LABEL_29:
  v11 = fabs(*(double *)(v2 + 32));
  if ( v11 > 1.0e-10 )
  {
    if ( fabs(v11 - 1.0) > 1.0e-10 )
      goto LABEL_36;
    if ( *(double *)(v2 + 32) <= 0.0 )
      v12 = -1.0;
    else
      v12 = 1.0;
  }
  else
  {
    v12 = 0.0;
  }
  *(_QWORD *)(v2 + 32) = *(_QWORD *)&v12;
LABEL_36:
  v13 = fabs(*(double *)(v2 + 40));
  if ( v13 > 1.0e-10 )
  {
    if ( fabs(v13 - 1.0) > 1.0e-10 )
      goto LABEL_43;
    if ( *(double *)(v2 + 40) <= 0.0 )
      v14 = -1.0;
    else
      v14 = 1.0;
  }
  else
  {
    v14 = 0.0;
  }
  *(_QWORD *)(v2 + 40) = *(_QWORD *)&v14;
LABEL_43:
  v15 = fabs(*(double *)(v2 + 48));
  if ( v15 > 1.0e-10 )
  {
    if ( fabs(v15 - 1.0) > 1.0e-10 )
      goto LABEL_50;
    if ( *(double *)(v2 + 48) <= 0.0 )
      v16 = -1.0;
    else
      v16 = 1.0;
  }
  else
  {
    v16 = 0.0;
  }
  *(_QWORD *)(v2 + 48) = *(_QWORD *)&v16;
LABEL_50:
  v17 = fabs(*(double *)(v2 + 56));
  if ( v17 > 1.0e-10 )
  {
    if ( fabs(v17 - 1.0) > 1.0e-10 )
      goto LABEL_57;
    if ( *(double *)(v2 + 56) <= 0.0 )
      v18 = -1.0;
    else
      v18 = 1.0;
  }
  else
  {
    v18 = 0.0;
  }
  *(_QWORD *)(v2 + 56) = *(_QWORD *)&v18;
LABEL_57:
  v19 = fabs(*(double *)(v2 + 64));
  if ( v19 <= 1.0e-10 )
  {
    v20 = 0.0;
LABEL_63:
    *(_QWORD *)(v2 + 64) = *(_QWORD *)&v20;
    goto LABEL_64;
  }
  if ( fabs(v19 - 1.0) <= 1.0e-10 )
  {
    if ( *(double *)(v2 + 64) <= 0.0 )
      v20 = -1.0;
    else
      v20 = 1.0;
    goto LABEL_63;
  }
LABEL_64:
  if ( UF_VEC3_unitize(&v25, COERCE_UNSIGNED_INT64(1.0e-10), COERCE_UNSIGNED_INT64(1.0e-10) >> 32, &v26, &v25)
    && UF_VEC3_unitize(&v24, COERCE_UNSIGNED_INT64(1.0e-10), COERCE_UNSIGNED_INT64(1.0e-10) >> 32, &v26, &v24) )
  {
    UF_VEC3_cross(&v25, &v24, &v23);
    UF_VEC3_cross(&v23, &v25, &v24);
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}
// 1000906C: using guessed type int __cdecl UF_VEC3_copy(_DWORD, _DWORD);
// 100090B4: using guessed type int __cdecl UF_MTX3_copy(_DWORD, _DWORD);
// 100090C4: using guessed type int __cdecl UF_VEC3_cross(_DWORD, _DWORD, _DWORD);
// 100090C8: using guessed type int __cdecl UF_VEC3_unitize(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (100031B0) --------------------------------------------------------
int __thiscall sub_100031B0(int this, int a2, int a3)
{
   v26 = 0.0;
  v27 = 0.0;
  v28 = 1.0;
  v3 = *(double *)a3;
  v4 = *(double *)(a3 + 8);
  v31 = *(double *)this;
  v32 = *(double *)(this + 8);
  v20 = v3;
  v21 = v3 * -1.0;
  v22 = v3 + 3.141592653589793;
  v23 = 3.141592653589793 - v3;
  v24 = 3.141592653589793 - v3 * -1.0;
  v25 = v3 * -1.0 + 3.141592653589793;
  v14 = v4;
  v33 = -1.0 * v4;
  v15 = -1.0 * v4;
  v16 = v4 + 3.141592653589793;
  v17 = 3.141592653589793 - v4;
  v18 = 3.141592653589793 - v33;
  v19 = v33 + 3.141592653589793;
  if ( fabs(v31 - v32) <= dbl_1000C010 )
    *(double *)(this + 8) = v32 * -1.0;
  v5 = 0;
  v6 = 0;
  do
  {
    sub_10002220(a2, (int)&v30, *(&v20 + v6), v31, 0);
    UF_VEC3_unitize(&v30, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v29, &v30);
    UF_VEC3_is_equal(&v26, &v30, LODWORD(dbl_1000C010), v7, (char *)&v33 + 4);
    if ( HIDWORD(v33) )
    {
      ++v5;
      *(&v12 + v5) = *(&v20 + v6);
    }
    ++v6;
  }
  while ( v6 < 6 );
  qsort(&Base, v5 - 1, 8u, (int (__cdecl *)(const void *, const void *))PtFuncCompare);
  *(_QWORD *)a3 = *(_QWORD *)&Base;
  v8 = 0;
  v9 = 0;
  do
  {
    sub_10002220(a2, (int)&v30, *(&v14 + v9), v32, 0);
    UF_VEC3_unitize(&v30, LODWORD(dbl_1000C010), HIDWORD(dbl_1000C010), &v29, &v30);
    UF_VEC3_is_equal(&v26, &v30, LODWORD(dbl_1000C010), v10, (char *)&v33 + 4);
    if ( HIDWORD(v33) )
    {
      ++v8;
      *(&v12 + v8) = *(&v14 + v9);
    }
    ++v9;
  }
  while ( v9 < 6 );
  qsort(&Base, v8 - 1, 8u, (int (__cdecl *)(const void *, const void *))PtFuncCompare);
  result = a3;
  *(_QWORD *)(a3 + 8) = *(_QWORD *)&Base;
  return result;
}
// 100090C8: using guessed type int __cdecl UF_VEC3_unitize(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100090F8: using guessed type int __cdecl UF_VEC3_is_equal(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1000C010: using guessed type double dbl_1000C010

//----- (100024D0) --------------------------------------------------------
signed int __cdecl PtFuncCompare(int a1, int a2)
{
  signed int result; // eax@2

  if ( fabs(*(double *)a1 - *(double *)a2) > dbl_1000C010 )
  {
    if ( dbl_1000C010 + *(double *)a2 >= *(double *)a1 )
      result = -1;
    else
      result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}
// 1000C010: using guessed type double dbl_1000C010;
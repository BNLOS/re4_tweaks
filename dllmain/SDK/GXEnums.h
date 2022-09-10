typedef enum _GXCullMode
{
  GX_CULL_NONE,
  GX_CULL_FRONT,
  GX_CULL_BACK,
  GX_CULL_ALL
} GXCullMode;

typedef enum _GXCompare
{
  GX_NEVER,
  GX_LESS,
  GX_EQUAL,
  GX_LEQUAL,
  GX_GREATER,
  GX_NEQUAL,
  GX_GEQUAL,
  GX_ALWAYS
} GXCompare;

typedef enum _GXChannelID
{
  GX_COLOR0,
  GX_COLOR1,
  GX_ALPHA0,
  GX_ALPHA1,
  GX_COLOR0A0,
  GX_COLOR1A1,
  GX_COLOR_ZERO,
  GX_ALPHA_BUMP,
  GX_ALPHA_BUMPN,
  GX_COLOR_NULL = 0xFF
} GXChannelID;

typedef enum _GXColorSrc
{
  GX_SRC_REG = 0,
  GX_SRC_VTX
} GXColorSrc;

typedef enum _GXDiffuseFn
{
  GX_DF_NONE = 0,
  GX_DF_SIGN,
  GX_DF_CLAMP
} GXDiffuseFn;

typedef enum _GXAttnFn
{
  GX_AF_SPEC = 0,
  GX_AF_SPOT = 1,
  GX_AF_NONE
} GXAttnFn;

typedef enum _GXTevStageID
{
  GX_TEVSTAGE0,
  GX_TEVSTAGE1,
  GX_TEVSTAGE2,
  GX_TEVSTAGE3,
  GX_TEVSTAGE4,
  GX_TEVSTAGE5,
  GX_TEVSTAGE6,
  GX_TEVSTAGE7,
  GX_TEVSTAGE8,
  GX_TEVSTAGE9,
  GX_TEVSTAGE10,
  GX_TEVSTAGE11,
  GX_TEVSTAGE12,
  GX_TEVSTAGE13,
  GX_TEVSTAGE14,
  GX_TEVSTAGE15,
  GX_MAX_TEVSTAGE
} GXTevStageID;

typedef enum _GXTevMode
{
  GX_MODULATE,
  GX_DECAL,
  GX_BLEND,
  GX_REPLACE,
  GX_PASSCLR
} GXTevMode;

typedef enum _GXTexCoordID
{
  GX_TEXCOORD0 = 0x0,
  GX_TEXCOORD1,
  GX_TEXCOORD2,
  GX_TEXCOORD3,
  GX_TEXCOORD4,
  GX_TEXCOORD5,
  GX_TEXCOORD6,
  GX_TEXCOORD7,
  GX_MAX_TEXCOORD = 8,
  GX_TEXCOORD_NULL = 0xFF
} GXTexCoordID;

typedef enum _GXTexMapID
{
  GX_TEXMAP0,
  GX_TEXMAP1,
  GX_TEXMAP2,
  GX_TEXMAP3,
  GX_TEXMAP4,
  GX_TEXMAP5,
  GX_TEXMAP6,
  GX_TEXMAP7,
  GX_MAX_TEXMAP,

  GX_TEXMAP_NULL = 0xFF,
  GX_TEX_DISABLE = 0x100
} GXTexMapID;

typedef enum _GXAttr
{
  GX_VA_PNMTXIDX = 0,
  GX_VA_TEX0MTXIDX,
  GX_VA_TEX1MTXIDX,
  GX_VA_TEX2MTXIDX,
  GX_VA_TEX3MTXIDX,
  GX_VA_TEX4MTXIDX,
  GX_VA_TEX5MTXIDX,
  GX_VA_TEX6MTXIDX,
  GX_VA_TEX7MTXIDX,
  GX_VA_POS = 9,
  GX_VA_NRM,
  GX_VA_CLR0,
  GX_VA_CLR1,
  GX_VA_TEX0,
  GX_VA_TEX1,
  GX_VA_TEX2,
  GX_VA_TEX3,
  GX_VA_TEX4,
  GX_VA_TEX5,
  GX_VA_TEX6,
  GX_VA_TEX7,

  GX_POS_MTX_ARRAY,
  GX_NRM_MTX_ARRAY,
  GX_TEX_MTX_ARRAY,
  GX_LIGHT_ARRAY,
  GX_VA_NBT,
  GX_VA_MAX_ATTR,

  GX_VA_NULL = 0xFF
} GXAttr;

typedef enum _GXAttrType
{
  GX_NONE = 0,
  GX_DIRECT,
  GX_INDEX8,
  GX_INDEX16
} GXAttrType;

typedef enum _GXCompCnt
{
  GX_POS_XY = 0,
  GX_POS_XYZ = 1,
  GX_NRM_XYZ = 0,
  GX_NRM_NBT = 1,
  GX_NRM_NBT3 = 2,
  GX_CLR_RGB = 0,
  GX_CLR_RGBA = 1,
  GX_TEX_S = 0,
  GX_TEX_ST = 1
} GXCompCnt;

typedef enum _GXVtxFmt
{
  GX_VTXFMT0 = 0,
  GX_VTXFMT1,
  GX_VTXFMT2,
  GX_VTXFMT3,
  GX_VTXFMT4,
  GX_VTXFMT5,
  GX_VTXFMT6,
  GX_VTXFMT7,
  GX_MAX_VTXFMT
} GXVtxFmt;

typedef enum _GXCompType
{
  GX_U8 = 0,
  GX_S8 = 1,
  GX_U16 = 2,
  GX_S16 = 3,
  GX_F32 = 4,

  GX_RGB565 = 0,
  GX_RGB8 = 1,
  GX_RGBX8 = 2,
  GX_RGBA4 = 3,
  GX_RGBA6 = 4,
  GX_RGBA8 = 5
} GXCompType;

typedef enum _GXBlendMode
{
  GX_BM_NONE,
  GX_BM_BLEND,
  GX_BM_LOGIC,
  GX_BM_SUBTRACT,
  GX_MAX_BLENDMODE
} GXBlendMode;

typedef enum _GXBlendFactor
{
  GX_BL_ZERO,
  GX_BL_ONE,
  GX_BL_SRCCLR,
  GX_BL_INVSRCCLR,
  GX_BL_SRCALPHA,
  GX_BL_INVSRCALPHA,
  GX_BL_DSTALPHA,
  GX_BL_INVDSTALPHA,

  GX_BL_DSTCLR = GX_BL_SRCCLR,
  GX_BL_INVDSTCLR = GX_BL_INVSRCCLR
} GXBlendFactor;

typedef enum _GXLogicOp
{
  GX_LO_CLEAR,
  GX_LO_AND,
  GX_LO_REVAND,
  GX_LO_COPY,
  GX_LO_INVAND,
  GX_LO_NOOP,
  GX_LO_XOR,
  GX_LO_OR,
  GX_LO_NOR,
  GX_LO_EQUIV,
  GX_LO_INV,
  GX_LO_REVOR,
  GX_LO_INVCOPY,
  GX_LO_INVOR,
  GX_LO_NAND,
  GX_LO_SET
} GXLogicOp;

typedef enum _GXPrimitive
{
  GX_POINTS = 0xB8,
  GX_LINES = 0xA8,
  GX_LINESTRIP = 0xB0,
  GX_TRIANGLES = 0x90,
  GX_TRIANGLESTRIP = 0x98,
  GX_TRIANGLEFAN = 0xA0,
  GX_QUADS = 0x80
} GXPrimitive;
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Elspero Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ELSPERO_ELSPEROCONSENSUS_H
#define ELSPERO_ELSPEROCONSENSUS_H

#if defined(BUILD_ELSPERO_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/elspero-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBELSPEROCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define ELSPEROCONSENSUS_API_VER 0

typedef enum elsperoconsensus_error_t
{
    elsperoconsensus_ERR_OK = 0,
    elsperoconsensus_ERR_TX_INDEX,
    elsperoconsensus_ERR_TX_SIZE_MISMATCH,
    elsperoconsensus_ERR_TX_DESERIALIZE,
} elsperoconsensus_error;

/** Script verification flags */
enum
{
    elsperoconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    elsperoconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    elsperoconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    elsperoconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int elsperoconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, elsperoconsensus_error* err);

EXPORT_SYMBOL unsigned int elsperoconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // ELSPERO_ELSPEROCONSENSUS_H

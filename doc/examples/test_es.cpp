#include <botan/botan.h>
#include <stdio.h>

#if defined(BOTAN_HAS_ENTROPY_SRC_DEVICE)
  #include <botan/es_dev.h>
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_EGD)
  #include <botan/es_egd.h>
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_UNIX)
  #include <botan/es_unix.h>
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_BEOS)
  #include <botan/es_beos.h>
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_CAPI)
  #include <botan/es_capi.h>
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_WIN32)
  #include <botan/es_win32.h>
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_FTW)
  #include <botan/es_ftw.h>
#endif


using namespace Botan;

void test_entropy_source(EntropySource* es,
                         EntropySource* es2 = 0)
   {
   // sometimes iostreams really is just a pain

   printf("Polling '%s':\n", es->name().c_str());

   Entropy_Accumulator accum1(256);
   es->poll(accum1);

   Entropy_Accumulator accum2(256);
   if(es2)
      es2->poll(accum2);
   else
      es->poll(accum2);

   SecureVector<byte> polled1 = accum1.get_entropy_buffer();
   SecureVector<byte> polled2 = accum2.get_entropy_buffer();

   SecureVector<byte> compare(std::min(polled1.size(), polled2.size()));

   for(u32bit i = 0; i != compare.size(); ++i)
      compare[i] = polled1[i] ^ polled2[i];

   for(u32bit i = 0; i != compare.size(); ++i)
      printf("%02X", compare[i]);
   printf("\n");

   delete es;
   delete es2;
   }

int main()
   {
   LibraryInitializer init;

#if defined(BOTAN_HAS_ENTROPY_SRC_DEVICE)
   test_entropy_source(
      new Device_EntropySource(
         split_on("/dev/random:/dev/srandom:/dev/urandom", ':')
         )
      );
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_EGD)
   test_entropy_source(
      new EGD_EntropySource(split_on("/var/run/egd-pool:/dev/egd-pool", ':'))
      );
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_CAPI)
   test_entropy_source(new Win32_CAPI_EntropySource);
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_FTW)
   test_entropy_source(new FTW_EntropySource("/proc"),
                       new FTW_EntropySource("/proc"));
#endif


#if defined(BOTAN_HAS_ENTROPY_SRC_WIN32)
   test_entropy_source(new Win32_EntropySource);
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_BEOS)
   test_entropy_source(new BeOS_EntropySource);
#endif

#if defined(BOTAN_HAS_ENTROPY_SRC_UNIX)
   test_entropy_source(
      new Unix_EntropySource(split_on("/bin:/sbin:/usr/bin:/usr/sbin", ':'))
      );
#endif
   }

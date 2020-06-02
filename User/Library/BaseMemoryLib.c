/** @file
  Copyright (c) 2020, PMheart. All rights reserved.
  SPDX-License-Identifier: BSD-3-Clause
**/

#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#include <string.h>
#include <stdlib.h>

VOID *
EFIAPI
CopyMem (
  OUT VOID       *DestinationBuffer,
  IN CONST VOID  *SourceBuffer,
  IN UINTN       Length
  )
{
  return memmove (DestinationBuffer, SourceBuffer, Length);
}

VOID *
EFIAPI
SetMem (
  OUT VOID  *Buffer,
  IN UINTN  Length,
  IN UINT8  Value
  )
{
  return memset (Buffer, Value, Length);
}

VOID *
EFIAPI
ZeroMem (
  OUT VOID  *Buffer,
  IN UINTN  Length
  )
{
  return memset (Buffer, 0, Length);
}

INTN
EFIAPI
CompareMem (
  IN CONST VOID  *DestinationBuffer,
  IN CONST VOID  *SourceBuffer,
  IN UINTN       Length
  )
{
  return memcmp (DestinationBuffer, SourceBuffer, Length);
}

VOID *
EFIAPI
ScanMem16 (
  IN      CONST VOID                *Buffer,
  IN      UINTN                     Length,
  IN      UINT16                    Value
  )
{
  UINT16                      *Pointer;

  Pointer = (UINT16*)Buffer;

  for (UINTN i = 0; i < Length; ++i) {
    if (Pointer[i] == Value) {
      return Pointer;
    }
  }

  return NULL;
}

VOID *
EFIAPI
AllocatePool (
  IN UINTN  AllocationSize
  )
{
  return malloc (AllocationSize);
}

VOID *
EFIAPI
AllocateCopyPool (
  IN UINTN       AllocationSize,
  IN CONST VOID  *Buffer
  )
{
  VOID *Memory;

  ASSERT (Buffer != NULL);

  Memory = AllocatePool (AllocationSize);
  if (Memory != NULL) {
    Memory = CopyMem (Memory, Buffer, AllocationSize);
  }
  return Memory;
}

VOID *
EFIAPI
AllocateZeroPool (
  IN UINTN  AllocationSize
  )
{
  VOID *Memory;

  Memory = AllocatePool (AllocationSize);

  if (Memory != NULL) {
    Memory = ZeroMem (Memory, AllocationSize);
  }
  return Memory;
}

VOID *
ReallocatePool (
   UINTN            OldSize,
   UINTN            NewSize,
   VOID             *OldBuffer  OPTIONAL
  )
{
  VOID  *NewBuffer;

  NewBuffer = AllocateZeroPool (NewSize);
  if (NewBuffer != NULL && OldBuffer != NULL) {
    memcpy (NewBuffer, OldBuffer, MIN (OldSize, NewSize));
    free (OldBuffer);
  }
  return NewBuffer;
}

VOID
EFIAPI
FreePool (
  IN VOID   *Buffer
  )
{
  ASSERT (Buffer != NULL);
  free (Buffer);
}

GUID *
EFIAPI
CopyGuid (
  OUT GUID       *DestinationGuid,
  IN CONST GUID  *SourceGuid
  )
{
  memmove (DestinationGuid, SourceGuid, sizeof (GUID));
  return DestinationGuid;
}

BOOLEAN
EFIAPI
CompareGuid (
  IN CONST GUID  *Guid1,
  IN CONST GUID  *Guid2
  )
{
  return memcmp (Guid1, Guid2, sizeof (GUID)) == 0;
}

UINT16
EFIAPI
ReadUnaligned16 (
  IN CONST UINT16              *Buffer
  )
{
  UINT16 Value;
  memmove (&Value, Buffer, sizeof (UINT16));
  return Value;
}

UINT16
EFIAPI
WriteUnaligned16 (
  OUT UINT16                    *Buffer,
  IN  UINT16                    Value
  )
{
  ASSERT (Buffer != NULL);

  memmove (Buffer, &Value, sizeof (UINT16));
  return Value;
}

UINT32
EFIAPI
ReadUnaligned32 (
  IN CONST UINT32              *Buffer
  )
{
  UINT32 Value;
  memmove (&Value, Buffer, sizeof (UINT32));
  return Value;
}

UINT64
EFIAPI
ReadUnaligned64 (
  IN CONST UINT64              *Buffer
  )
{
  UINT64 Value;
  memmove (&Value, Buffer, sizeof (UINT64));
  return Value;
}

UINT32
EFIAPI
WriteUnaligned32 (
  OUT UINT32                    *Buffer,
  IN  UINT32                    Value
  )
{
  ASSERT (Buffer != NULL);

  memmove (Buffer, &Value, sizeof (UINT32));
  return Value;
}

UINT64
EFIAPI
WriteUnaligned64 (
  OUT UINT64                    *Buffer,
  IN  UINT64                    Value
  )
{
  ASSERT (Buffer != NULL);

  memmove (Buffer, &Value, sizeof (UINT64));
  return Value;
}

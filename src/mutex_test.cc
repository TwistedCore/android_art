/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mutex.h"

#include "gtest/gtest.h"

namespace art {

#if !defined(__APPLE__)
struct MutexTester {
  static void AssertDepth(Mutex& mu, uint32_t expected_depth) {
    ASSERT_EQ(expected_depth, mu.GetDepth());
  }
};

TEST(Mutex, LockUnlock) {
  Mutex mu("test mutex");
  MutexTester::AssertDepth(mu, 0U);
  mu.Lock();
  MutexTester::AssertDepth(mu, 1U);
  mu.Unlock();
  MutexTester::AssertDepth(mu, 0U);
}

TEST(Mutex, TryLockUnlock) {
  Mutex mu("test mutex");
  MutexTester::AssertDepth(mu, 0U);
  mu.TryLock();
  MutexTester::AssertDepth(mu, 1U);
  mu.Unlock();
  MutexTester::AssertDepth(mu, 0U);
}

TEST(Mutex, RecursiveLockUnlock) {
  Mutex mu("test mutex");
  MutexTester::AssertDepth(mu, 0U);
  mu.Lock();
  MutexTester::AssertDepth(mu, 1U);
  mu.Lock();
  MutexTester::AssertDepth(mu, 2U);
  mu.Unlock();
  MutexTester::AssertDepth(mu, 1U);
  mu.Unlock();
  MutexTester::AssertDepth(mu, 0U);
}

TEST(Mutex, RecursiveTryLockUnlock) {
  Mutex mu("test mutex");
  MutexTester::AssertDepth(mu, 0U);
  mu.TryLock();
  MutexTester::AssertDepth(mu, 1U);
  mu.TryLock();
  MutexTester::AssertDepth(mu, 2U);
  mu.Unlock();
  MutexTester::AssertDepth(mu, 1U);
  mu.Unlock();
  MutexTester::AssertDepth(mu, 0U);
}
#endif

}  // namespace art

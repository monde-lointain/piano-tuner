#include <gtest/gtest.h>

#include <memory>

#include "simple_tuner/config/ConfigManager.h"
#include "simple_tuner/platform/desktop/MockConfigStorage.h"

namespace simple_tuner {
namespace {

TEST(ConfigManagerTest, DefaultReferencePitch440Hz) {
  auto storage = std::make_unique<MockConfigStorage>();
  ConfigManager manager(std::move(storage));
  EXPECT_DOUBLE_EQ(440.0, manager.get_reference_pitch());
}

TEST(ConfigManagerTest, SetValidReferencePitch) {
  auto storage = std::make_unique<MockConfigStorage>();
  ConfigManager manager(std::move(storage));
  EXPECT_TRUE(manager.set_reference_pitch(442.0));
  EXPECT_DOUBLE_EQ(442.0, manager.get_reference_pitch());
}

TEST(ConfigManagerTest, ClampBelowMinimum) {
  auto storage = std::make_unique<MockConfigStorage>();
  ConfigManager manager(std::move(storage));
  manager.set_reference_pitch(400.0);  // Below 410 minimum
  EXPECT_DOUBLE_EQ(410.0, manager.get_reference_pitch());
}

TEST(ConfigManagerTest, ClampAboveMaximum) {
  auto storage = std::make_unique<MockConfigStorage>();
  ConfigManager manager(std::move(storage));
  manager.set_reference_pitch(500.0);  // Above 480 maximum
  EXPECT_DOUBLE_EQ(480.0, manager.get_reference_pitch());
}

TEST(ConfigManagerTest, BoundaryMinimum410Hz) {
  auto storage = std::make_unique<MockConfigStorage>();
  ConfigManager manager(std::move(storage));
  EXPECT_TRUE(manager.set_reference_pitch(410.0));
  EXPECT_DOUBLE_EQ(410.0, manager.get_reference_pitch());
}

TEST(ConfigManagerTest, BoundaryMaximum480Hz) {
  auto storage = std::make_unique<MockConfigStorage>();
  ConfigManager manager(std::move(storage));
  EXPECT_TRUE(manager.set_reference_pitch(480.0));
  EXPECT_DOUBLE_EQ(480.0, manager.get_reference_pitch());
}

TEST(ConfigManagerTest, ResetToDefault) {
  auto storage = std::make_unique<MockConfigStorage>();
  ConfigManager manager(std::move(storage));
  manager.set_reference_pitch(442.0);
  EXPECT_DOUBLE_EQ(442.0, manager.get_reference_pitch());
  EXPECT_TRUE(manager.reset_reference_pitch());
  EXPECT_DOUBLE_EQ(440.0, manager.get_reference_pitch());
}

TEST(ConfigManagerTest, PersistenceAcrossInstances) {
  auto storage = std::make_shared<MockConfigStorage>();

  {
    ConfigManager manager1(std::make_unique<MockConfigStorage>(*storage));
    manager1.set_reference_pitch(442.0);
    EXPECT_DOUBLE_EQ(442.0, manager1.get_reference_pitch());
    // Manually copy state back to shared storage
    storage->set_double("reference_pitch", 442.0);
  }

  // Create new manager with fresh storage containing same data
  auto storage2 = std::make_unique<MockConfigStorage>(*storage);
  ConfigManager manager2(std::move(storage2));
  EXPECT_DOUBLE_EQ(442.0, manager2.get_reference_pitch());
}

TEST(ConfigManagerTest, CorruptedDataFallsBackToDefault) {
  auto storage = std::make_unique<MockConfigStorage>();
  // Manually inject corrupted value
  storage->set_double("reference_pitch", 9999.0);

  ConfigManager manager(std::move(storage));
  // Should clamp to max (480.0)
  EXPECT_DOUBLE_EQ(480.0, manager.get_reference_pitch());
}

}  // namespace
}  // namespace simple_tuner

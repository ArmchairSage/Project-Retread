<script setup lang="ts">
import { Menu } from '@lucide/vue';

const sendClickHandler = async () => {
  console.log("SENDING MESSAGE");
  const response = await fetch("http://192.168.4.32:8000/send-msg", { method: "POST"});
};

</script>

<template>
  <v-app>
    <v-app-bar color="primary">
      <template v-slot:prepend>
        <v-app-bar-nav-icon><Menu /></v-app-bar-nav-icon>
      </template>

      <v-app-bar-title>Signal Client</v-app-bar-title>
    </v-app-bar>
    <v-main>
      <v-container>
        <v-btn block class="bg-blue" @click="sendClickHandler">Send</v-btn>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped></style>
